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
struct ks_wlan_private {int /*<<< orphan*/  devread_wait; int /*<<< orphan*/  dev_read_lock; int /*<<< orphan*/  multicast_spin; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostif_aplist_init (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_counters_init (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_pmklist_init (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_power_save_init (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_sme_init (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_status_init (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  hostif_wpa_init (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int hostif_init(struct ks_wlan_private *priv)
{
	hostif_aplist_init(priv);
	hostif_status_init(priv);

	spin_lock_init(&priv->multicast_spin);
	spin_lock_init(&priv->dev_read_lock);
	init_waitqueue_head(&priv->devread_wait);

	hostif_counters_init(priv);
	hostif_power_save_init(priv);
	hostif_wpa_init(priv);
	hostif_pmklist_init(priv);
	hostif_sme_init(priv);

	return 0;
}