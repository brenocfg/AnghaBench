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
typedef  size_t u16 ;
struct i40e_vsi {size_t num_queue_pairs; int /*<<< orphan*/ * rx_rings; void* rx_buf_len; void* max_frame; TYPE_2__* netdev; TYPE_1__* back; } ;
struct TYPE_4__ {scalar_t__ mtu; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 scalar_t__ ETH_DATA_LEN ; 
 int /*<<< orphan*/  I40E_2K_TOO_SMALL_WITH_PADDING ; 
 int I40E_FLAG_LEGACY_RX ; 
 void* I40E_MAX_RXBUFFER ; 
 void* I40E_RXBUFFER_1536 ; 
 void* I40E_RXBUFFER_2048 ; 
 void* I40E_RXBUFFER_3072 ; 
 void* NET_IP_ALIGN ; 
 int PAGE_SIZE ; 
 int i40e_configure_rx_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_vsi_configure_rx(struct i40e_vsi *vsi)
{
	int err = 0;
	u16 i;

	if (!vsi->netdev || (vsi->back->flags & I40E_FLAG_LEGACY_RX)) {
		vsi->max_frame = I40E_MAX_RXBUFFER;
		vsi->rx_buf_len = I40E_RXBUFFER_2048;
#if (PAGE_SIZE < 8192)
	} else if (!I40E_2K_TOO_SMALL_WITH_PADDING &&
		   (vsi->netdev->mtu <= ETH_DATA_LEN)) {
		vsi->max_frame = I40E_RXBUFFER_1536 - NET_IP_ALIGN;
		vsi->rx_buf_len = I40E_RXBUFFER_1536 - NET_IP_ALIGN;
#endif
	} else {
		vsi->max_frame = I40E_MAX_RXBUFFER;
		vsi->rx_buf_len = (PAGE_SIZE < 8192) ? I40E_RXBUFFER_3072 :
						       I40E_RXBUFFER_2048;
	}

	/* set up individual rings */
	for (i = 0; i < vsi->num_queue_pairs && !err; i++)
		err = i40e_configure_rx_ring(vsi->rx_rings[i]);

	return err;
}