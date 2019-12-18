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
struct stk_camera {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_AEB ; 
 int /*<<< orphan*/  REG_AEW ; 
 int /*<<< orphan*/  max (int,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  stk_sensor_outb (struct stk_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int stk_sensor_set_brightness(struct stk_camera *dev, int br)
{
	if (br < 0 || br > 0xff)
		return -EINVAL;
	stk_sensor_outb(dev, REG_AEB, max(0x00, br - 6));
	stk_sensor_outb(dev, REG_AEW, min(0xff, br + 6));
	return 0;
}