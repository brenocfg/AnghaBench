#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ir_raw_event {int pulse; int /*<<< orphan*/  duration; } ;
struct au0828_rc {int /*<<< orphan*/  rc; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 int AU8522_UNIT ; 
 int /*<<< orphan*/  DEV_DISCONNECTED ; 
 int /*<<< orphan*/  NEC_START_PULSE ; 
 int NEC_START_SPACE ; 
 int /*<<< orphan*/  RC5_START_PULSE ; 
 int /*<<< orphan*/  au8522_rc_clear (struct au0828_rc*,int,int) ; 
 int au8522_rc_read (struct au0828_rc*,int,int,unsigned char*,int) ; 
 int /*<<< orphan*/  au8522_rc_set (struct au0828_rc*,int,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  ir_raw_event_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_raw_event_store (int /*<<< orphan*/ ,struct ir_raw_event*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int au0828_get_key_au8522(struct au0828_rc *ir)
{
	unsigned char buf[40];
	struct ir_raw_event rawir = {};
	int i, j, rc;
	int prv_bit, bit, width;
	bool first = true;

	/* do nothing if device is disconnected */
	if (test_bit(DEV_DISCONNECTED, &ir->dev->dev_state))
		return 0;

	/* Check IR int */
	rc = au8522_rc_read(ir, 0xe1, -1, buf, 1);
	if (rc < 0 || !(buf[0] & (1 << 4))) {
		/* Be sure that IR is enabled */
		au8522_rc_set(ir, 0xe0, 1 << 4);
		return 0;
	}

	/* Something arrived. Get the data */
	rc = au8522_rc_read(ir, 0xe3, 0x11, buf, sizeof(buf));


	if (rc < 0)
		return rc;

	/* Disable IR */
	au8522_rc_clear(ir, 0xe0, 1 << 4);

	/* Enable IR */
	au8522_rc_set(ir, 0xe0, 1 << 4);

	dprintk(16, "RC data received: %*ph\n", 40, buf);

	prv_bit = (buf[0] >> 7) & 0x01;
	width = 0;
	for (i = 0; i < sizeof(buf); i++) {
		for (j = 7; j >= 0; j--) {
			bit = (buf[i] >> j) & 0x01;
			if (bit == prv_bit) {
				width++;
				continue;
			}

			/*
			 * Fix an au8522 bug: the first pulse event
			 * is lost. So, we need to fake it, based on the
			 * protocol. That means that not all raw decoders
			 * will work, as we need to add a hack for each
			 * protocol, based on the first space.
			 * So, we only support RC5 and NEC.
			 */

			if (first) {
				first = false;

				rawir.pulse = true;
				if (width > NEC_START_SPACE - 2 &&
				    width < NEC_START_SPACE + 2) {
					/* NEC protocol */
					rawir.duration = NEC_START_PULSE;
					dprintk(16, "Storing NEC start %s with duration %d",
						rawir.pulse ? "pulse" : "space",
						rawir.duration);
				} else {
					/* RC5 protocol */
					rawir.duration = RC5_START_PULSE;
					dprintk(16, "Storing RC5 start %s with duration %d",
						rawir.pulse ? "pulse" : "space",
						rawir.duration);
				}
				ir_raw_event_store(ir->rc, &rawir);
			}

			rawir.pulse = prv_bit ? false : true;
			rawir.duration = AU8522_UNIT * width;
			dprintk(16, "Storing %s with duration %d",
				rawir.pulse ? "pulse" : "space",
				rawir.duration);
			ir_raw_event_store(ir->rc, &rawir);

			width = 1;
			prv_bit = bit;
		}
	}

	rawir.pulse = prv_bit ? false : true;
	rawir.duration = AU8522_UNIT * width;
	dprintk(16, "Storing end %s with duration %d",
		rawir.pulse ? "pulse" : "space",
		rawir.duration);
	ir_raw_event_store(ir->rc, &rawir);

	ir_raw_event_handle(ir->rc);

	return 1;
}