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
struct uniphier_u3hsphy_trim_param {int /*<<< orphan*/  hs_i; int /*<<< orphan*/  sel_t; int /*<<< orphan*/  rterm; } ;
struct uniphier_u3hsphy_priv {int dummy; } ;

/* Variables and functions */
 int uniphier_u3hsphy_get_nvparam (struct uniphier_u3hsphy_priv*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uniphier_u3hsphy_get_nvparams(struct uniphier_u3hsphy_priv *priv,
					 struct uniphier_u3hsphy_trim_param *pt)
{
	int ret;

	ret = uniphier_u3hsphy_get_nvparam(priv, "rterm", &pt->rterm);
	if (ret)
		return ret;

	ret = uniphier_u3hsphy_get_nvparam(priv, "sel_t", &pt->sel_t);
	if (ret)
		return ret;

	ret = uniphier_u3hsphy_get_nvparam(priv, "hs_i", &pt->hs_i);
	if (ret)
		return ret;

	return 0;
}