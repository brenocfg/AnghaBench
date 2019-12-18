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
struct reg_action {int /*<<< orphan*/  value; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct rapl_package {TYPE_1__* priv; } ;
struct TYPE_2__ {scalar_t__ (* read_raw ) (int,struct reg_action*) ;int /*<<< orphan*/ ** regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
#define  RAPL_DOMAIN_DRAM 132 
#define  RAPL_DOMAIN_PACKAGE 131 
#define  RAPL_DOMAIN_PLATFORM 130 
#define  RAPL_DOMAIN_PP0 129 
#define  RAPL_DOMAIN_PP1 128 
 size_t RAPL_DOMAIN_REG_STATUS ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ stub1 (int,struct reg_action*) ; 

__attribute__((used)) static int rapl_check_domain(int cpu, int domain, struct rapl_package *rp)
{
	struct reg_action ra;

	switch (domain) {
	case RAPL_DOMAIN_PACKAGE:
	case RAPL_DOMAIN_PP0:
	case RAPL_DOMAIN_PP1:
	case RAPL_DOMAIN_DRAM:
		ra.reg = rp->priv->regs[domain][RAPL_DOMAIN_REG_STATUS];
		break;
	case RAPL_DOMAIN_PLATFORM:
		/* PSYS(PLATFORM) is not a CPU domain, so avoid printng error */
		return -EINVAL;
	default:
		pr_err("invalid domain id %d\n", domain);
		return -EINVAL;
	}
	/* make sure domain counters are available and contains non-zero
	 * values, otherwise skip it.
	 */

	ra.mask = ~0;
	if (rp->priv->read_raw(cpu, &ra) || !ra.value)
		return -ENODEV;

	return 0;
}