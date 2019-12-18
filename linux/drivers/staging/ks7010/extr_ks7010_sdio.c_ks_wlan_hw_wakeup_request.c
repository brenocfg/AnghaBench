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
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct ks_wlan_private {int /*<<< orphan*/  wakeup_count; int /*<<< orphan*/  last_wakeup; int /*<<< orphan*/  net_dev; TYPE_1__ psstatus; } ;

/* Variables and functions */
 scalar_t__ PS_SNOOZE ; 
 int /*<<< orphan*/  WAKEUP_REG ; 
 int /*<<< orphan*/  WAKEUP_REQ ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int ks7010_sdio_writeb (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

void ks_wlan_hw_wakeup_request(struct ks_wlan_private *priv)
{
	int ret;

	if (atomic_read(&priv->psstatus.status) == PS_SNOOZE) {
		ret = ks7010_sdio_writeb(priv, WAKEUP_REG, WAKEUP_REQ);
		if (ret)
			netdev_err(priv->net_dev, "write WAKEUP_REG\n");

		priv->last_wakeup = jiffies;
		++priv->wakeup_count;
	}
}