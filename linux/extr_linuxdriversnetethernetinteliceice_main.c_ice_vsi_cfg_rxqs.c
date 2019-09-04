#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct ice_vsi {scalar_t__ max_frame; size_t num_rxq; TYPE_2__* back; int /*<<< orphan*/ * rx_rings; void* rx_buf_len; TYPE_3__* netdev; } ;
struct TYPE_6__ {scalar_t__ mtu; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ETH_DATA_LEN ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_HLEN ; 
 void* ICE_RXBUF_2048 ; 
 scalar_t__ VLAN_HLEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ice_setup_rx_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_vsi_cfg_rxqs(struct ice_vsi *vsi)
{
	int err = 0;
	u16 i;

	if (vsi->netdev && vsi->netdev->mtu > ETH_DATA_LEN)
		vsi->max_frame = vsi->netdev->mtu +
			ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	else
		vsi->max_frame = ICE_RXBUF_2048;

	vsi->rx_buf_len = ICE_RXBUF_2048;
	/* set up individual rings */
	for (i = 0; i < vsi->num_rxq && !err; i++)
		err = ice_setup_rx_ctx(vsi->rx_rings[i]);

	if (err) {
		dev_err(&vsi->back->pdev->dev, "ice_setup_rx_ctx failed\n");
		return -EIO;
	}
	return err;
}