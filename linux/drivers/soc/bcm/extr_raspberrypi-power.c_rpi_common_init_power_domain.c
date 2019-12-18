#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__** domains; } ;
struct rpi_power_domains {TYPE_1__ xlate; int /*<<< orphan*/  fw; struct rpi_power_domain* domains; } ;
struct TYPE_4__ {char const* name; int /*<<< orphan*/  power_off; int /*<<< orphan*/  power_on; } ;
struct rpi_power_domain {TYPE_2__ base; int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_genpd_init (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rpi_domain_off ; 
 int /*<<< orphan*/  rpi_domain_on ; 

__attribute__((used)) static void rpi_common_init_power_domain(struct rpi_power_domains *rpi_domains,
					 int xlate_index, const char *name)
{
	struct rpi_power_domain *dom = &rpi_domains->domains[xlate_index];

	dom->fw = rpi_domains->fw;

	dom->base.name = name;
	dom->base.power_on = rpi_domain_on;
	dom->base.power_off = rpi_domain_off;

	/*
	 * Treat all power domains as off at boot.
	 *
	 * The firmware itself may be keeping some domains on, but
	 * from Linux's perspective all we control is the refcounts
	 * that we give to the firmware, and we can't ask the firmware
	 * to turn off something that we haven't ourselves turned on.
	 */
	pm_genpd_init(&dom->base, NULL, true);

	rpi_domains->xlate.domains[xlate_index] = &dom->base;
}