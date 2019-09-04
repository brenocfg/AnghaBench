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
 int /*<<< orphan*/  MO_GP1_IO ; 
#define  XC2028_TUNER_RESET 128 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int cx88_xc3028_winfast1800h_callback(struct cx88_core *core,
					     int command, int arg)
{
	switch (command) {
	case XC2028_TUNER_RESET:
		/* GPIO 12 (xc3028 tuner reset) */
		cx_set(MO_GP1_IO, 0x1010);
		mdelay(50);
		cx_clear(MO_GP1_IO, 0x10);
		mdelay(75);
		cx_set(MO_GP1_IO, 0x10);
		mdelay(75);
		return 0;
	}
	return -EINVAL;
}