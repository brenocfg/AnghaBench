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
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  wakeup_request; } ;
struct ks_wlan_private {int sleep_mode; TYPE_1__ sleepstatus; int /*<<< orphan*/  wakeup_count; int /*<<< orphan*/  last_wakeup; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAKEUP_REG ; 
 int /*<<< orphan*/  WAKEUP_REQ ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int ks7010_sdio_writeb (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ks_wlan_hw_sleep_wakeup_request(struct ks_wlan_private *priv)
{
	int ret;

	/* clear request */
	atomic_set(&priv->sleepstatus.wakeup_request, 0);

	if (atomic_read(&priv->sleepstatus.status) == 1) {
		ret = ks7010_sdio_writeb(priv, WAKEUP_REG, WAKEUP_REQ);
		if (ret) {
			netdev_err(priv->net_dev, "write WAKEUP_REG\n");
			goto set_sleep_mode;
		}
		atomic_set(&priv->sleepstatus.status, 0);
		priv->last_wakeup = jiffies;
		++priv->wakeup_count;
	}

set_sleep_mode:
	priv->sleep_mode = atomic_read(&priv->sleepstatus.status);
}