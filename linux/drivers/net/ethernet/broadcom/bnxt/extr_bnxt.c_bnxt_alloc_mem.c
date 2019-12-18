#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_18__ {void* flags; } ;
struct TYPE_19__ {TYPE_7__ ring_mem; } ;
struct bnxt_tx_ring_info {int txq_index; TYPE_9__* bnapi; TYPE_8__ tx_ring_struct; } ;
struct TYPE_16__ {void* flags; } ;
struct TYPE_17__ {TYPE_5__ ring_mem; } ;
struct TYPE_14__ {void* flags; } ;
struct TYPE_15__ {TYPE_3__ ring_mem; } ;
struct bnxt_rx_ring_info {TYPE_9__* bnapi; TYPE_6__ rx_agg_ring_struct; TYPE_4__ rx_ring_struct; } ;
struct bnxt_napi {int dummy; } ;
struct TYPE_12__ {void* flags; } ;
struct TYPE_13__ {TYPE_1__ ring_mem; } ;
struct bnxt_cp_ring_info {TYPE_2__ cp_ring_struct; } ;
struct bnxt {int cp_nr_rings; int flags; int rx_nr_rings; int tx_nr_rings; int* tx_ring_map; int tx_nr_rings_xdp; TYPE_10__* vnic_info; TYPE_9__** bnapi; struct bnxt_tx_ring_info* tx_ring; struct bnxt_rx_ring_info* rx_ring; } ;
struct TYPE_20__ {int index; int /*<<< orphan*/  tx_int; int /*<<< orphan*/  flags; struct bnxt_tx_ring_info* tx_ring; struct bnxt_rx_ring_info* rx_ring; struct bnxt_cp_ring_info cp_ring; struct bnxt* bp; } ;
struct TYPE_11__ {int flags; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_SHARED_RINGS ; 
 int /*<<< orphan*/  BNXT_NAPI_FLAG_XDP ; 
 void* BNXT_RMEM_RING_PTE_FLAG ; 
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
			if (bp->flags & BNXT_FLAG_CHIP_P5) {
				struct bnxt_cp_ring_info *cpr =
					&bp->bnapi[i]->cp_ring;

				cpr->cp_ring_struct.ring_mem.flags =
					BNXT_RMEM_RING_PTE_FLAG;
			}
		}

		bp->rx_ring = kcalloc(bp->rx_nr_rings,
				      sizeof(struct bnxt_rx_ring_info),
				      GFP_KERNEL);
		if (!bp->rx_ring)
			return -ENOMEM;

		for (i = 0; i < bp->rx_nr_rings; i++) {
			struct bnxt_rx_ring_info *rxr = &bp->rx_ring[i];

			if (bp->flags & BNXT_FLAG_CHIP_P5) {
				rxr->rx_ring_struct.ring_mem.flags =
					BNXT_RMEM_RING_PTE_FLAG;
				rxr->rx_agg_ring_struct.ring_mem.flags =
					BNXT_RMEM_RING_PTE_FLAG;
			}
			rxr->bnapi = bp->bnapi[i];
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
			struct bnxt_tx_ring_info *txr = &bp->tx_ring[i];

			if (bp->flags & BNXT_FLAG_CHIP_P5)
				txr->tx_ring_struct.ring_mem.flags =
					BNXT_RMEM_RING_PTE_FLAG;
			txr->bnapi = bp->bnapi[j];
			bp->bnapi[j]->tx_ring = txr;
			bp->tx_ring_map[i] = bp->tx_nr_rings_xdp + i;
			if (i >= bp->tx_nr_rings_xdp) {
				txr->txq_index = i - bp->tx_nr_rings_xdp;
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