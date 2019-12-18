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
typedef  int /*<<< orphan*/  u16 ;
struct b53_device {int /*<<< orphan*/  jumbo_size_reg; int /*<<< orphan*/  jumbo_pm_reg; int /*<<< orphan*/  enabled_ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_JUMBO_PAGE ; 
 int EINVAL ; 
 int /*<<< orphan*/  JMS_MAX_SIZE ; 
 int /*<<< orphan*/  JMS_MIN_SIZE ; 
 int /*<<< orphan*/  JPM_10_100_JUMBO_EN ; 
 int b53_write16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_write32 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is5325 (struct b53_device*) ; 
 scalar_t__ is5365 (struct b53_device*) ; 

__attribute__((used)) static int b53_set_jumbo(struct b53_device *dev, bool enable, bool allow_10_100)
{
	u32 port_mask = 0;
	u16 max_size = JMS_MIN_SIZE;

	if (is5325(dev) || is5365(dev))
		return -EINVAL;

	if (enable) {
		port_mask = dev->enabled_ports;
		max_size = JMS_MAX_SIZE;
		if (allow_10_100)
			port_mask |= JPM_10_100_JUMBO_EN;
	}

	b53_write32(dev, B53_JUMBO_PAGE, dev->jumbo_pm_reg, port_mask);
	return b53_write16(dev, B53_JUMBO_PAGE, dev->jumbo_size_reg, max_size);
}