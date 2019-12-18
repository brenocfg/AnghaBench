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
struct rapl_if_priv {int (* read_raw ) (int /*<<< orphan*/ ,struct reg_action*) ;struct rapl_domain* platform_rapl_domain; int /*<<< orphan*/  control_type; int /*<<< orphan*/ ** regs; } ;
struct rapl_domain {size_t id; int /*<<< orphan*/  power_zone; int /*<<< orphan*/  rp; TYPE_1__* rpl; int /*<<< orphan*/ * regs; int /*<<< orphan*/  name; } ;
struct powercap_zone {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  prim_id; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct powercap_zone*) ; 
 int /*<<< orphan*/  PL1_ENABLE ; 
 int /*<<< orphan*/  PL2_ENABLE ; 
 int PTR_ERR (struct powercap_zone*) ; 
 size_t RAPL_DOMAIN_PLATFORM ; 
 size_t RAPL_DOMAIN_REG_LIMIT ; 
 size_t RAPL_DOMAIN_REG_STATUS ; 
 int /*<<< orphan*/  constraint_ops ; 
 int /*<<< orphan*/  kfree (struct rapl_domain*) ; 
 struct rapl_domain* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl1_name ; 
 int /*<<< orphan*/  pl2_name ; 
 struct powercap_zone* powercap_register_zone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rapl_domain_names ; 
 int /*<<< orphan*/  rapl_find_package_domain (int /*<<< orphan*/ ,struct rapl_if_priv*) ; 
 int stub1 (int /*<<< orphan*/ ,struct reg_action*) ; 
 int stub2 (int /*<<< orphan*/ ,struct reg_action*) ; 
 int /*<<< orphan*/ * zone_ops ; 

int rapl_add_platform_domain(struct rapl_if_priv *priv)
{
	struct rapl_domain *rd;
	struct powercap_zone *power_zone;
	struct reg_action ra;
	int ret;

	ra.reg = priv->regs[RAPL_DOMAIN_PLATFORM][RAPL_DOMAIN_REG_STATUS];
	ra.mask = ~0;
	ret = priv->read_raw(0, &ra);
	if (ret || !ra.value)
		return -ENODEV;

	ra.reg = priv->regs[RAPL_DOMAIN_PLATFORM][RAPL_DOMAIN_REG_LIMIT];
	ra.mask = ~0;
	ret = priv->read_raw(0, &ra);
	if (ret || !ra.value)
		return -ENODEV;

	rd = kzalloc(sizeof(*rd), GFP_KERNEL);
	if (!rd)
		return -ENOMEM;

	rd->name = rapl_domain_names[RAPL_DOMAIN_PLATFORM];
	rd->id = RAPL_DOMAIN_PLATFORM;
	rd->regs[RAPL_DOMAIN_REG_LIMIT] =
	    priv->regs[RAPL_DOMAIN_PLATFORM][RAPL_DOMAIN_REG_LIMIT];
	rd->regs[RAPL_DOMAIN_REG_STATUS] =
	    priv->regs[RAPL_DOMAIN_PLATFORM][RAPL_DOMAIN_REG_STATUS];
	rd->rpl[0].prim_id = PL1_ENABLE;
	rd->rpl[0].name = pl1_name;
	rd->rpl[1].prim_id = PL2_ENABLE;
	rd->rpl[1].name = pl2_name;
	rd->rp = rapl_find_package_domain(0, priv);

	power_zone = powercap_register_zone(&rd->power_zone, priv->control_type,
					    "psys", NULL,
					    &zone_ops[RAPL_DOMAIN_PLATFORM],
					    2, &constraint_ops);

	if (IS_ERR(power_zone)) {
		kfree(rd);
		return PTR_ERR(power_zone);
	}

	priv->platform_rapl_domain = rd;

	return 0;
}