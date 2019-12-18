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
struct uniphier_u3hsphy_trim_param {int /*<<< orphan*/  hs_i; int /*<<< orphan*/  sel_t; int /*<<< orphan*/  rterm; } ;
struct uniphier_u3hsphy_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HSPHY_CFG0_HS_I_MASK ; 
 int /*<<< orphan*/  HSPHY_CFG0_RTERM_MASK ; 
 int /*<<< orphan*/  HSPHY_CFG0_SEL_T_MASK ; 

__attribute__((used)) static void uniphier_u3hsphy_trim_ld20(struct uniphier_u3hsphy_priv *priv,
				       u32 *pconfig,
				       struct uniphier_u3hsphy_trim_param *pt)
{
	*pconfig &= ~HSPHY_CFG0_RTERM_MASK;
	*pconfig |= FIELD_PREP(HSPHY_CFG0_RTERM_MASK, pt->rterm);

	*pconfig &= ~HSPHY_CFG0_SEL_T_MASK;
	*pconfig |= FIELD_PREP(HSPHY_CFG0_SEL_T_MASK, pt->sel_t);

	*pconfig &= ~HSPHY_CFG0_HS_I_MASK;
	*pconfig |= FIELD_PREP(HSPHY_CFG0_HS_I_MASK,  pt->hs_i);
}