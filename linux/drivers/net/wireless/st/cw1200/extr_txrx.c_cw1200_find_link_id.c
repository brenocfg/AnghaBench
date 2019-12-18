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
typedef  int /*<<< orphan*/  u8 ;
struct cw1200_common {int /*<<< orphan*/  ps_state_lock; TYPE_1__* link_id_db; } ;
struct TYPE_2__ {int /*<<< orphan*/  timestamp; scalar_t__ status; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int CW1200_MAX_STA_IN_AP_MODE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int cw1200_find_link_id(struct cw1200_common *priv, const u8 *mac)
{
	int i, ret = 0;
	spin_lock_bh(&priv->ps_state_lock);
	for (i = 0; i < CW1200_MAX_STA_IN_AP_MODE; ++i) {
		if (!memcmp(mac, priv->link_id_db[i].mac, ETH_ALEN) &&
		    priv->link_id_db[i].status) {
			priv->link_id_db[i].timestamp = jiffies;
			ret = i + 1;
			break;
		}
	}
	spin_unlock_bh(&priv->ps_state_lock);
	return ret;
}