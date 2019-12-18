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
struct timer_list {int dummy; } ;
struct stmmac_priv {int /*<<< orphan*/  eee_ctrl_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMMAC_LPI_T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eee_ctrl_timer ; 
 int /*<<< orphan*/  eee_timer ; 
 struct stmmac_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct stmmac_priv* priv ; 
 int /*<<< orphan*/  stmmac_enable_eee_mode (struct stmmac_priv*) ; 

__attribute__((used)) static void stmmac_eee_ctrl_timer(struct timer_list *t)
{
	struct stmmac_priv *priv = from_timer(priv, t, eee_ctrl_timer);

	stmmac_enable_eee_mode(priv);
	mod_timer(&priv->eee_ctrl_timer, STMMAC_LPI_T(eee_timer));
}