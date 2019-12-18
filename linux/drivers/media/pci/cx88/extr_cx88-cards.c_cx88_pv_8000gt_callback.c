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
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MO_GP2_IO ; 
#define  XC2028_TUNER_RESET 128 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int cx88_pv_8000gt_callback(struct cx88_core *core,
				   int command, int arg)
{
	switch (command) {
	case XC2028_TUNER_RESET:
		cx_write(MO_GP2_IO, 0xcf7);
		mdelay(50);
		cx_write(MO_GP2_IO, 0xef5);
		mdelay(50);
		cx_write(MO_GP2_IO, 0xcf7);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}