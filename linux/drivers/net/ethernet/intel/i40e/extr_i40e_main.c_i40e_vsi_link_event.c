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
struct i40e_vsi {int type; int /*<<< orphan*/  netdev; int /*<<< orphan*/  netdev_registered; int /*<<< orphan*/  state; } ;

/* Variables and functions */
#define  I40E_VSI_CTRL 133 
#define  I40E_VSI_IWARP 132 
#define  I40E_VSI_MAIN 131 
#define  I40E_VSI_MIRROR 130 
#define  I40E_VSI_SRIOV 129 
#define  I40E_VSI_VMDQ2 128 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_vsi_link_event(struct i40e_vsi *vsi, bool link_up)
{
	if (!vsi || test_bit(__I40E_VSI_DOWN, vsi->state))
		return;

	switch (vsi->type) {
	case I40E_VSI_MAIN:
		if (!vsi->netdev || !vsi->netdev_registered)
			break;

		if (link_up) {
			netif_carrier_on(vsi->netdev);
			netif_tx_wake_all_queues(vsi->netdev);
		} else {
			netif_carrier_off(vsi->netdev);
			netif_tx_stop_all_queues(vsi->netdev);
		}
		break;

	case I40E_VSI_SRIOV:
	case I40E_VSI_VMDQ2:
	case I40E_VSI_CTRL:
	case I40E_VSI_IWARP:
	case I40E_VSI_MIRROR:
	default:
		/* there is no notification for other VSIs */
		break;
	}
}