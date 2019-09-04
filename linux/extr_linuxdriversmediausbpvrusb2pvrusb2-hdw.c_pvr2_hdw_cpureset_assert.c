#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pvr2_hdw {int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  PVR2_TRACE_ERROR_LEGS ; 
 int /*<<< orphan*/  PVR2_TRACE_INIT ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_hdw_render_useless (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 
 int usb_control_msg (int /*<<< orphan*/ ,unsigned int,int,int,int,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pvr2_hdw_cpureset_assert(struct pvr2_hdw *hdw,int val)
{
	char *da;
	unsigned int pipe;
	int ret;

	if (!hdw->usb_dev) return;

	da = kmalloc(16, GFP_KERNEL);

	if (da == NULL) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "Unable to allocate memory to control CPU reset");
		return;
	}

	pvr2_trace(PVR2_TRACE_INIT,"cpureset_assert(%d)",val);

	da[0] = val ? 0x01 : 0x00;

	/* Write the CPUCS register on the 8051.  The lsb of the register
	   is the reset bit; a 1 asserts reset while a 0 clears it. */
	pipe = usb_sndctrlpipe(hdw->usb_dev, 0);
	ret = usb_control_msg(hdw->usb_dev,pipe,0xa0,0x40,0xe600,0,da,1,HZ);
	if (ret < 0) {
		pvr2_trace(PVR2_TRACE_ERROR_LEGS,
			   "cpureset_assert(%d) error=%d",val,ret);
		pvr2_hdw_render_useless(hdw);
	}

	kfree(da);
}