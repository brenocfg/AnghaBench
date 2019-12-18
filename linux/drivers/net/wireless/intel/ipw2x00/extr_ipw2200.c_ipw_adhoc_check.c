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
struct TYPE_2__ {int /*<<< orphan*/  beacon_interval; } ;
struct ipw_priv {scalar_t__ disassociate_threshold; int config; TYPE_1__ assoc_request; int /*<<< orphan*/  adhoc_check; int /*<<< orphan*/  missed_adhoc_beacons; } ;

/* Variables and functions */
 int CFG_ADHOC_PERSIST ; 
 int /*<<< orphan*/  IPW_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int IPW_DL_ASSOC ; 
 int IPW_DL_INFO ; 
 int IPW_DL_NOTIF ; 
 int IPW_DL_STATE ; 
 int /*<<< orphan*/  ipw_disassociate (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_remove_current_network (struct ipw_priv*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipw_adhoc_check(void *data)
{
	struct ipw_priv *priv = data;

	if (priv->missed_adhoc_beacons++ > priv->disassociate_threshold &&
	    !(priv->config & CFG_ADHOC_PERSIST)) {
		IPW_DEBUG(IPW_DL_INFO | IPW_DL_NOTIF |
			  IPW_DL_STATE | IPW_DL_ASSOC,
			  "Missed beacon: %d - disassociate\n",
			  priv->missed_adhoc_beacons);
		ipw_remove_current_network(priv);
		ipw_disassociate(priv);
		return;
	}

	schedule_delayed_work(&priv->adhoc_check,
			      le16_to_cpu(priv->assoc_request.beacon_interval));
}