#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_10__ {struct pvr2_hdw* algo_data; int /*<<< orphan*/ * algo; TYPE_2__ dev; int /*<<< orphan*/  name; } ;
struct pvr2_hdw {size_t unit_number; scalar_t__ ir_scheme_active; int i2c_linked; int /*<<< orphan*/ ** i2c_func; TYPE_4__ i2c_adap; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  i2c_algo; TYPE_3__* usb_dev; int /*<<< orphan*/  name; TYPE_1__* hdw_desc; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ flag_has_wm8775; scalar_t__ flag_has_cx25840; } ;

/* Variables and functions */
 unsigned int PVR2_I2C_FUNC_CNT ; 
 scalar_t__ PVR2_IR_SCHEME_24XXX ; 
 scalar_t__ PVR2_IR_SCHEME_24XXX_MCE ; 
 int /*<<< orphan*/  PVR2_TRACE_INFO ; 
 scalar_t__ do_i2c_probe (struct pvr2_hdw*,int) ; 
 int /*<<< orphan*/  do_i2c_scan (struct pvr2_hdw*) ; 
 int /*<<< orphan*/ * i2c_24xxx_ir ; 
 int /*<<< orphan*/  i2c_add_adapter (TYPE_4__*) ; 
 int /*<<< orphan*/ * i2c_black_hole ; 
 int /*<<< orphan*/ * i2c_hack_cx25840 ; 
 int /*<<< orphan*/ * i2c_hack_wm8775 ; 
 scalar_t__ i2c_scan ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int* ir_mode ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 TYPE_4__ pvr2_i2c_adap_template ; 
 int /*<<< orphan*/  pvr2_i2c_algo_template ; 
 int /*<<< orphan*/ * pvr2_i2c_basic_op ; 
 int /*<<< orphan*/  pvr2_i2c_register_ir (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void pvr2_i2c_core_init(struct pvr2_hdw *hdw)
{
	unsigned int idx;

	/* The default action for all possible I2C addresses is just to do
	   the transfer normally. */
	for (idx = 0; idx < PVR2_I2C_FUNC_CNT; idx++) {
		hdw->i2c_func[idx] = pvr2_i2c_basic_op;
	}

	/* However, deal with various special cases for 24xxx hardware. */
	if (ir_mode[hdw->unit_number] == 0) {
		pr_info("%s: IR disabled\n", hdw->name);
		hdw->i2c_func[0x18] = i2c_black_hole;
	} else if (ir_mode[hdw->unit_number] == 1) {
		if (hdw->ir_scheme_active == PVR2_IR_SCHEME_24XXX) {
			/* Set up translation so that our IR looks like a
			   29xxx device */
			hdw->i2c_func[0x18] = i2c_24xxx_ir;
		}
	}
	if (hdw->hdw_desc->flag_has_cx25840) {
		hdw->i2c_func[0x44] = i2c_hack_cx25840;
	}
	if (hdw->hdw_desc->flag_has_wm8775) {
		hdw->i2c_func[0x1b] = i2c_hack_wm8775;
	}

	// Configure the adapter and set up everything else related to it.
	hdw->i2c_adap = pvr2_i2c_adap_template;
	hdw->i2c_algo = pvr2_i2c_algo_template;
	strscpy(hdw->i2c_adap.name, hdw->name, sizeof(hdw->i2c_adap.name));
	hdw->i2c_adap.dev.parent = &hdw->usb_dev->dev;
	hdw->i2c_adap.algo = &hdw->i2c_algo;
	hdw->i2c_adap.algo_data = hdw;
	hdw->i2c_linked = !0;
	i2c_set_adapdata(&hdw->i2c_adap, &hdw->v4l2_dev);
	i2c_add_adapter(&hdw->i2c_adap);
	if (hdw->i2c_func[0x18] == i2c_24xxx_ir) {
		/* Probe for a different type of IR receiver on this
		   device.  This is really the only way to differentiate
		   older 24xxx devices from 24xxx variants that include an
		   IR blaster.  If the IR blaster is present, the IR
		   receiver is part of that chip and thus we must disable
		   the emulated IR receiver. */
		if (do_i2c_probe(hdw, 0x71)) {
			pvr2_trace(PVR2_TRACE_INFO,
				   "Device has newer IR hardware; disabling unneeded virtual IR device");
			hdw->i2c_func[0x18] = NULL;
			/* Remember that this is a different device... */
			hdw->ir_scheme_active = PVR2_IR_SCHEME_24XXX_MCE;
		}
	}
	if (i2c_scan) do_i2c_scan(hdw);

	pvr2_i2c_register_ir(hdw);
}