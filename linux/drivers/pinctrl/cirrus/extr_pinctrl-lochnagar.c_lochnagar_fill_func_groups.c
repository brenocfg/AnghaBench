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
struct lochnagar_pin_priv {int ngroups; TYPE_1__* groups; struct lochnagar_func_groups* func_groups; int /*<<< orphan*/  dev; } ;
struct lochnagar_func_groups {scalar_t__ ngroups; int /*<<< orphan*/ * groups; } ;
struct TYPE_2__ {size_t type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LN_FTYPE_COUNT ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lochnagar_fill_func_groups(struct lochnagar_pin_priv *priv)
{
	struct lochnagar_func_groups *funcs;
	int i;

	for (i = 0; i < priv->ngroups; i++)
		priv->func_groups[priv->groups[i].type].ngroups++;

	for (i = 0; i < LN_FTYPE_COUNT; i++) {
		funcs = &priv->func_groups[i];

		if (!funcs->ngroups)
			continue;

		funcs->groups = devm_kcalloc(priv->dev, funcs->ngroups,
					     sizeof(*funcs->groups),
					     GFP_KERNEL);
		if (!funcs->groups)
			return -ENOMEM;

		funcs->ngroups = 0;
	}

	for (i = 0; i < priv->ngroups; i++) {
		funcs = &priv->func_groups[priv->groups[i].type];

		funcs->groups[funcs->ngroups++] = priv->groups[i].name;
	}

	return 0;
}