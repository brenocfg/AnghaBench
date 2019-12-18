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
struct ks_wlan_private {int /*<<< orphan*/  dev_state; int /*<<< orphan*/  connect_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_READY ; 
 int /*<<< orphan*/  SME_POW_MNGMT_REQUEST ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_connect_status (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks_wlan_do_power_save(struct ks_wlan_private *priv)
{
	if (is_connect_status(priv->connect_status))
		hostif_sme_enqueue(priv, SME_POW_MNGMT_REQUEST);
	else
		priv->dev_state = DEVICE_STATE_READY;
}