#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  power_off; int /*<<< orphan*/  power_on; int /*<<< orphan*/  name; } ;
struct owl_sps_domain {TYPE_4__ genpd; TYPE_2__* info; struct owl_sps* sps; } ;
struct TYPE_7__ {TYPE_4__** domains; } ;
struct owl_sps {TYPE_3__ genpd_data; TYPE_1__* info; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  genpd_flags; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_2__* domains; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct owl_sps_domain* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owl_sps_power_off ; 
 int /*<<< orphan*/  owl_sps_power_on ; 
 int /*<<< orphan*/  pm_genpd_init (TYPE_4__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int owl_sps_init_domain(struct owl_sps *sps, int index)
{
	struct owl_sps_domain *pd;

	pd = devm_kzalloc(sps->dev, sizeof(*pd), GFP_KERNEL);
	if (!pd)
		return -ENOMEM;

	pd->info = &sps->info->domains[index];
	pd->sps = sps;

	pd->genpd.name = pd->info->name;
	pd->genpd.power_on = owl_sps_power_on;
	pd->genpd.power_off = owl_sps_power_off;
	pd->genpd.flags = pd->info->genpd_flags;
	pm_genpd_init(&pd->genpd, NULL, false);

	sps->genpd_data.domains[index] = &pd->genpd;

	return 0;
}