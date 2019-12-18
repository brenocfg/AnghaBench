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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CTRL ; 
 int /*<<< orphan*/  GPIO_CTRL_VAL2 ; 
 int /*<<< orphan*/  RT3290 ; 
 int /*<<< orphan*/  WLAN_FUN_CTRL ; 
 int /*<<< orphan*/  WLAN_GPIO_IN_BIT0 ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

int rt2800_rfkill_poll(struct rt2x00_dev *rt2x00dev)
{
	u32 reg;

	if (rt2x00_rt(rt2x00dev, RT3290)) {
		reg = rt2800_register_read(rt2x00dev, WLAN_FUN_CTRL);
		return rt2x00_get_field32(reg, WLAN_GPIO_IN_BIT0);
	} else {
		reg = rt2800_register_read(rt2x00dev, GPIO_CTRL);
		return rt2x00_get_field32(reg, GPIO_CTRL_VAL2);
	}
}