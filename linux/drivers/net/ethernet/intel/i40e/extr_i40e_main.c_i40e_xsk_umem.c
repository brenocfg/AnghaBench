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
struct xdp_umem {int dummy; } ;
struct i40e_ring {int queue_index; TYPE_1__* vsi; } ;
struct TYPE_2__ {int /*<<< orphan*/  netdev; int /*<<< orphan*/  af_xdp_zc_qps; scalar_t__ alloc_queue_pairs; } ;

/* Variables and functions */
 int i40e_enabled_xdp_vsi (TYPE_1__*) ; 
 scalar_t__ ring_is_xdp (struct i40e_ring*) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 struct xdp_umem* xdp_get_umem_from_qid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct xdp_umem *i40e_xsk_umem(struct i40e_ring *ring)
{
	bool xdp_on = i40e_enabled_xdp_vsi(ring->vsi);
	int qid = ring->queue_index;

	if (ring_is_xdp(ring))
		qid -= ring->vsi->alloc_queue_pairs;

	if (!xdp_on || !test_bit(qid, ring->vsi->af_xdp_zc_qps))
		return NULL;

	return xdp_get_umem_from_qid(ring->vsi->netdev, qid);
}