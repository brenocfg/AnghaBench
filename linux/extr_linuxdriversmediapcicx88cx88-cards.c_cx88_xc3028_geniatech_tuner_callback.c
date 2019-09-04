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
struct cx88_core {int /*<<< orphan*/  input; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  CX88_RADIO 130 
#define  CX88_VMUX_DVB 129 
 int EINVAL ; 
 TYPE_1__ INPUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MO_GP1_IO ; 
#define  XC2028_TUNER_RESET 128 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int cx88_xc3028_geniatech_tuner_callback(struct cx88_core *core,
						int command, int mode)
{
	switch (command) {
	case XC2028_TUNER_RESET:
		switch (INPUT(core->input).type) {
		case CX88_RADIO:
			break;
		case CX88_VMUX_DVB:
			cx_write(MO_GP1_IO, 0x030302);
			mdelay(50);
			break;
		default:
			cx_write(MO_GP1_IO, 0x030301);
			mdelay(50);
		}
		cx_write(MO_GP1_IO, 0x101010);
		mdelay(50);
		cx_write(MO_GP1_IO, 0x101000);
		mdelay(50);
		cx_write(MO_GP1_IO, 0x101010);
		mdelay(50);
		return 0;
	}
	return -EINVAL;
}