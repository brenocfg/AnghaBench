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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ power_mgmt; scalar_t__ operation_mode; } ;
struct ks_wlan_private {TYPE_1__ reg; } ;

/* Variables and functions */
 scalar_t__ MODE_INFRASTRUCTURE ; 
 int POWER_ACTIVE ; 
 scalar_t__ POWER_MGMT_SAVE1 ; 
 scalar_t__ POWER_MGMT_SAVE2 ; 
 int POWER_SAVE ; 
 int /*<<< orphan*/  hostif_power_mgmt_request (struct ks_wlan_private*,int,int,int) ; 

__attribute__((used)) static void hostif_sme_power_mgmt_set(struct ks_wlan_private *priv)
{
	u32 mode, wake_up, receive_dtims;

	if (priv->reg.power_mgmt != POWER_MGMT_SAVE1 &&
	    priv->reg.power_mgmt != POWER_MGMT_SAVE2) {
		mode = POWER_ACTIVE;
		wake_up = 0;
		receive_dtims = 0;
	} else {
		mode = (priv->reg.operation_mode == MODE_INFRASTRUCTURE) ?
			POWER_SAVE : POWER_ACTIVE;
		wake_up = 0;
		receive_dtims = (priv->reg.operation_mode == MODE_INFRASTRUCTURE &&
				 priv->reg.power_mgmt == POWER_MGMT_SAVE2);
	}

	hostif_power_mgmt_request(priv, mode, wake_up, receive_dtims);
}