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
typedef  scalar_t__ u32 ;
struct vxge_hw_ring_rxd_1 {int /*<<< orphan*/  control_1; } ;
struct __vxge_hw_ring {int dummy; } ;

/* Variables and functions */
 scalar_t__ VXGE_HW_RING_RXD_1_BUFFER0_SIZE_GET (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void vxge_hw_ring_rxd_1b_get(
	struct __vxge_hw_ring *ring_handle,
	void *rxdh,
	u32 *pkt_length)
{
	struct vxge_hw_ring_rxd_1 *rxdp = (struct vxge_hw_ring_rxd_1 *)rxdh;

	*pkt_length =
		(u32)VXGE_HW_RING_RXD_1_BUFFER0_SIZE_GET(rxdp->control_1);
}