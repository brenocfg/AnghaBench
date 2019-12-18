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
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct cw1200_common* priv; } ;
struct cw1200_common {int /*<<< orphan*/  pm_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  cw1200_debug_init (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_pm_deinit (int /*<<< orphan*/ *) ; 
 int cw1200_pm_init (int /*<<< orphan*/ *,struct cw1200_common*) ; 
 int ieee80211_register_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cw1200_register_common(struct ieee80211_hw *dev)
{
	struct cw1200_common *priv = dev->priv;
	int err;

#ifdef CONFIG_PM
	err = cw1200_pm_init(&priv->pm_state, priv);
	if (err) {
		pr_err("Cannot init PM. (%d).\n",
		       err);
		return err;
	}
#endif

	err = ieee80211_register_hw(dev);
	if (err) {
		pr_err("Cannot register device (%d).\n",
		       err);
#ifdef CONFIG_PM
		cw1200_pm_deinit(&priv->pm_state);
#endif
		return err;
	}

	cw1200_debug_init(priv);

	pr_info("Registered as '%s'\n", wiphy_name(dev->wiphy));
	return 0;
}