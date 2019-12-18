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
struct vnt_private {TYPE_1__* pcid; int /*<<< orphan*/  interrupt_work; } ;
struct ieee80211_hw {struct vnt_private* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARDbRadioPowerOff (struct vnt_private*) ; 
 int /*<<< orphan*/  MACbShutdown (struct vnt_private*) ; 
 int /*<<< orphan*/  MACbSoftwareReset (struct vnt_private*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_free_rd0_ring (struct vnt_private*) ; 
 int /*<<< orphan*/  device_free_rd1_ring (struct vnt_private*) ; 
 int /*<<< orphan*/  device_free_rings (struct vnt_private*) ; 
 int /*<<< orphan*/  device_free_td0_ring (struct vnt_private*) ; 
 int /*<<< orphan*/  device_free_td1_ring (struct vnt_private*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct vnt_private*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (struct ieee80211_hw*) ; 

__attribute__((used)) static void vnt_stop(struct ieee80211_hw *hw)
{
	struct vnt_private *priv = hw->priv;

	ieee80211_stop_queues(hw);

	cancel_work_sync(&priv->interrupt_work);

	MACbShutdown(priv);
	MACbSoftwareReset(priv);
	CARDbRadioPowerOff(priv);

	device_free_td0_ring(priv);
	device_free_td1_ring(priv);
	device_free_rd0_ring(priv);
	device_free_rd1_ring(priv);
	device_free_rings(priv);

	free_irq(priv->pcid->irq, priv);
}