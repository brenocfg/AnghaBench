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
struct ieee80211_vif {int /*<<< orphan*/  p2p; int /*<<< orphan*/  type; int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct hwsim_vif_priv {scalar_t__ magic; } ;

/* Variables and functions */
 scalar_t__ HWSIM_VIF_MAGIC ; 
 int /*<<< orphan*/  WARN (int,char*,struct ieee80211_vif*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hwsim_check_magic(struct ieee80211_vif *vif)
{
	struct hwsim_vif_priv *vp = (void *)vif->drv_priv;
	WARN(vp->magic != HWSIM_VIF_MAGIC,
	     "Invalid VIF (%p) magic %#x, %pM, %d/%d\n",
	     vif, vp->magic, vif->addr, vif->type, vif->p2p);
}