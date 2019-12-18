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
struct rapl_package {int /*<<< orphan*/ * domains; } ;
struct rapl_domain {scalar_t__ id; struct rapl_package* rp; } ;
struct powercap_zone {int dummy; } ;

/* Variables and functions */
 scalar_t__ RAPL_DOMAIN_PACKAGE ; 
 int /*<<< orphan*/  kfree (struct rapl_domain*) ; 
 struct rapl_domain* power_zone_to_rapl_domain (struct powercap_zone*) ; 

__attribute__((used)) static int release_zone(struct powercap_zone *power_zone)
{
	struct rapl_domain *rd = power_zone_to_rapl_domain(power_zone);
	struct rapl_package *rp = rd->rp;

	/* package zone is the last zone of a package, we can free
	 * memory here since all children has been unregistered.
	 */
	if (rd->id == RAPL_DOMAIN_PACKAGE) {
		kfree(rd);
		rp->domains = NULL;
	}

	return 0;

}