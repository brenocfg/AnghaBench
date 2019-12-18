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
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  REG_SW_CTRL_6 ; 
 int /*<<< orphan*/  SW_MIB_COUNTER_FREEZE ; 
 int /*<<< orphan*/  ksz_cfg (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ksz8795_freeze_mib(struct ksz_device *dev, int port, bool freeze)
{
	/* enable the port for flush/freeze function */
	if (freeze)
		ksz_cfg(dev, REG_SW_CTRL_6, BIT(port), true);
	ksz_cfg(dev, REG_SW_CTRL_6, SW_MIB_COUNTER_FREEZE, freeze);

	/* disable the port after freeze is done */
	if (!freeze)
		ksz_cfg(dev, REG_SW_CTRL_6, BIT(port), false);
}