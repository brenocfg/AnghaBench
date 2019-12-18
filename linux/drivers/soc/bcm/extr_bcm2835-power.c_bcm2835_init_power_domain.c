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
struct device {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {char const* name; int /*<<< orphan*/  power_off; int /*<<< orphan*/  power_on; } ;
struct bcm2835_power_domain {int domain; TYPE_2__ base; struct bcm2835_power* power; int /*<<< orphan*/ * clk; } ;
struct TYPE_3__ {TYPE_2__** domains; } ;
struct bcm2835_power {TYPE_1__ pd_xlate; struct bcm2835_power_domain* domains; struct device* dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcm2835_power_pd_power_off ; 
 int /*<<< orphan*/  bcm2835_power_pd_power_on ; 
 int /*<<< orphan*/ * devm_clk_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pm_genpd_init (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
bcm2835_init_power_domain(struct bcm2835_power *power,
			  int pd_xlate_index, const char *name)
{
	struct device *dev = power->dev;
	struct bcm2835_power_domain *dom = &power->domains[pd_xlate_index];

	dom->clk = devm_clk_get(dev->parent, name);
	if (IS_ERR(dom->clk)) {
		int ret = PTR_ERR(dom->clk);

		if (ret == -EPROBE_DEFER)
			return ret;

		/* Some domains don't have a clk, so make sure that we
		 * don't deref an error pointer later.
		 */
		dom->clk = NULL;
	}

	dom->base.name = name;
	dom->base.power_on = bcm2835_power_pd_power_on;
	dom->base.power_off = bcm2835_power_pd_power_off;

	dom->domain = pd_xlate_index;
	dom->power = power;

	/* XXX: on/off at boot? */
	pm_genpd_init(&dom->base, NULL, true);

	power->pd_xlate.domains[pd_xlate_index] = &dom->base;

	return 0;
}