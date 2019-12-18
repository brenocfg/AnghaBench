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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct rmobile_pm_domain {scalar_t__ base; TYPE_1__ genpd; int /*<<< orphan*/  bit_shift; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 scalar_t__ PSTR ; 
 int /*<<< orphan*/  PSTR_DELAY_US ; 
 int PSTR_RETRIES ; 
 scalar_t__ SWUCR ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __rmobile_pd_power_up(struct rmobile_pm_domain *rmobile_pd)
{
	unsigned int mask = BIT(rmobile_pd->bit_shift);
	unsigned int retry_count;
	int ret = 0;

	if (__raw_readl(rmobile_pd->base + PSTR) & mask)
		return ret;

	__raw_writel(mask, rmobile_pd->base + SWUCR);

	for (retry_count = 2 * PSTR_RETRIES; retry_count; retry_count--) {
		if (!(__raw_readl(rmobile_pd->base + SWUCR) & mask))
			break;
		if (retry_count > PSTR_RETRIES)
			udelay(PSTR_DELAY_US);
		else
			cpu_relax();
	}
	if (!retry_count)
		ret = -EIO;

	pr_debug("%s: Power on, 0x%08x -> PSTR = 0x%08x\n",
		 rmobile_pd->genpd.name, mask,
		 __raw_readl(rmobile_pd->base + PSTR));

	return ret;
}