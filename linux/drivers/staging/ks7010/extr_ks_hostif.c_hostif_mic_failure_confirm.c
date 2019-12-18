#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  failure; } ;
struct TYPE_4__ {TYPE_1__ mic_failure; } ;
struct ks_wlan_private {TYPE_2__ wpa; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SME_MIC_FAILURE_CONFIRM ; 
 int /*<<< orphan*/  hostif_sme_enqueue (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void hostif_mic_failure_confirm(struct ks_wlan_private *priv)
{
	netdev_dbg(priv->net_dev, "mic_failure=%u\n",
		   priv->wpa.mic_failure.failure);
	hostif_sme_enqueue(priv, SME_MIC_FAILURE_CONFIRM);
}