#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct bnxt_tx_ring_info {int dummy; } ;
struct bnxt_rx_ring_info {int dummy; } ;
struct bnxt_napi {int dummy; } ;
struct bnxt {int cp_nr_rings; int rx_nr_rings; int tx_nr_rings; int* tx_ring_map; int flags; int tx_nr_rings_xdp; TYPE_4__* vnic_info; TYPE_3__** bnapi; TYPE_2__* tx_ring; TYPE_1__* rx_ring; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {int index; int /*<<< orphan*/  tx_int; int /*<<< orphan*/  flags; TYPE_2__* tx_ring; TYPE_1__* rx_ring; struct bnxt* bp; } ;
struct TYPE_6__ {int txq_index; TYPE_3__* bnapi; } ;
struct TYPE_5__ {TYPE_3__* bnapi; } ;

/* Variables and functions */
 int BNXT_FLAG_SHARED_RINGS ; 
 int /*<<< orphan*/  BNXT_NAPI_FLAG_XDP ; 
 int BNXT_VNIC_MCAST_FLAG ; 
 int BNXT_VNIC_RSS_FLAG ; 
 int BNXT_VNIC_UCAST_FLAG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int L1_CACHE_ALIGN (int) ; 
 int bnxt_alloc_cp_rings (struct bnxt*) ; 
 int bnxt_alloc_ntp_fltrs (struct bnxt*) ; 
 int bnxt_alloc_rx_rings (struct bnxt*) ; 
 int bnxt_alloc_stats (struct bnxt*) ; 
 int bnxt_alloc_tx_rings (struct bnxt*) ; 
 int bnxt_alloc_vnic_attributes (struct bnxt*) ; 
 int bnxt_alloc_vnics (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_mem (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_init_ring_struct (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_tx_int ; 
 int /*<<< orphan*/  bnxt_tx_int_xdp ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_alloc_mem(struct bnxt *bp, bool irq_re_init)
{
	int i, j, rc, size, arr_size;
	void *bnapi;

	if (irq_re_init) {
		/* Allocate bnapi mem pointer array and mem block for
		 * all queues
		 */
		arr_size = L1_CACHE_ALIGN(sizeof(struct bnxt_napi *) *
				bp->cp_nr_rings);
		size = L1_CACHE_ALIGN(sizeof(struct bnxt_napi));
		bnapi = kzalloc(arr_size + size * bp->cp_nr_rings, GFP_KERNEL);
		if (!bnapi)
			return -ENOMEM;

		bp->bnapi = bnapi;
		bnapi += arr_size;
		for (i = 0; i < bp->cp_nr_rings; i++, bnapi += size) {
			bp->bnapi[i] = bnapi;
			bp->bnapi[i]->index = i;
			bp->bnapi[i]->bp = bp;
		}

		bp->rx_ring = kcalloc(bp->rx_nr_rings,
				      sizeof(struct bnxt_rx_ring_info),
				      GFP_KERNEL);
		if (!bp->rx_ring)
			return -ENOMEM;

		for (i = 0; i < bp->rx_nr_rings; i++) {
			bp->rx_ring[i].bnapi = bp->bnapi[i];
			bp->bnapi[i]->rx_ring = &bp->rx_ring[i];
		}

		bp->tx_ring = kcalloc(bp->tx_nr_rings,
				      sizeof(struct bnxt_tx_ring_info),
				      GFP_KERNEL);
		if (!bp->tx_ring)
			return -ENOMEM;

		bp->tx_ring_map = kcalloc(bp->tx_nr_rings, sizeof(u16),
					  GFP_KERNEL);

		if (!bp->tx_ring_map)
			return -ENOMEM;

		if (bp->flags & BNXT_FLAG_SHARED_RINGS)
			j = 0;
		else
			j = bp->rx_nr_rings;

		for (i = 0; i < bp->tx_nr_rings; i++, j++) {
			bp->tx_ring[i].bnapi = bp->bnapi[j];
			bp->bnapi[j]->tx_ring = &bp->tx_ring[i];
			bp->tx_ring_map[i] = bp->tx_nr_rings_xdp + i;
			if (i >= bp->tx_nr_rings_xdp) {
				bp->tx_ring[i].txq_index = i -
					bp->tx_nr_rings_xdp;
				bp->bnapi[j]->tx_int = bnxt_tx_int;
			} else {
				bp->bnapi[j]->flags |= BNXT_NAPI_FLAG_XDP;
				bp->bnapi[j]->tx_int = bnxt_tx_int_xdp;
			}
		}

		rc = bnxt_alloc_stats(bp);
		if (rc)
			goto alloc_mem_err;

		rc = bnxt_alloc_ntp_fltrs(bp);
		if (rc)
			goto alloc_mem_err;

		rc = bnxt_alloc_vnics(bp);
		if (rc)
			goto alloc_mem_err;
	}

	bnxt_init_ring_struct(bp);

	rc = bnxt_alloc_rx_rings(bp);
	if (rc)
		goto alloc_mem_err;

	rc = bnxt_alloc_tx_rings(bp);
	if (rc)
		goto alloc_mem_err;

	rc = bnxt_alloc_cp_rings(bp);
	if (rc)
		goto alloc_mem_err;

	bp->vnic_info[0].flags |= BNXT_VNIC_RSS_FLAG | BNXT_VNIC_MCAST_FLAG |
				  BNXT_VNIC_UCAST_FLAG;
	rc = bnxt_alloc_vnic_attributes(bp);
	if (rc)
		goto alloc_mem_err;
	return 0;

alloc_mem_err:
	bnxt_free_mem(bp, true);
	return rc;
}