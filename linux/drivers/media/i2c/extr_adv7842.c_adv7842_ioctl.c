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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
#define  ADV7842_CMD_RAM_TEST 128 
 long ENOTTY ; 
 long adv7842_command_ram_test (struct v4l2_subdev*) ; 

__attribute__((used)) static long adv7842_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	switch (cmd) {
	case ADV7842_CMD_RAM_TEST:
		return adv7842_command_ram_test(sd);
	}
	return -ENOTTY;
}