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
struct TYPE_4__ {int /*<<< orphan*/  confirm_wait; } ;
struct TYPE_3__ {scalar_t__ power_mgmt; scalar_t__ operation_mode; } ;
struct ks_wlan_private {int /*<<< orphan*/  dev_state; TYPE_2__ psstatus; TYPE_1__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_READY ; 
 int /*<<< orphan*/  DEVICE_STATE_SLEEP ; 
 scalar_t__ MODE_INFRASTRUCTURE ; 
 scalar_t__ POWER_MGMT_ACTIVE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_wlan_hw_power_save (struct ks_wlan_private*) ; 

__attribute__((used)) static
void hostif_power_mgmt_confirm(struct ks_wlan_private *priv)
{
	if (priv->reg.power_mgmt > POWER_MGMT_ACTIVE &&
	    priv->reg.operation_mode == MODE_INFRASTRUCTURE) {
		atomic_set(&priv->psstatus.confirm_wait, 0);
		priv->dev_state = DEVICE_STATE_SLEEP;
		ks_wlan_hw_power_save(priv);
	} else {
		priv->dev_state = DEVICE_STATE_READY;
	}
}