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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct rx_tpa_end_cmp {int dummy; } ;
struct rx_cmp {int /*<<< orphan*/  rx_cmp_misc_v1; } ;
struct bnxt_cp_ring_info {int dummy; } ;
struct bnxt {int flags; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 scalar_t__ CMP_TYPE_RX_L2_CMP ; 
 scalar_t__ CMP_TYPE_RX_L2_TPA_END_CMP ; 
 int EBUSY ; 
 scalar_t__ RX_CMP_AGG_BUFS ; 
 scalar_t__ RX_CMP_AGG_BUFS_SHIFT ; 
 scalar_t__ RX_CMP_TYPE (struct rx_cmp*) ; 
 scalar_t__ TPA_END_AGG_BUFS (struct rx_tpa_end_cmp*) ; 
 int /*<<< orphan*/  bnxt_agg_bufs_valid (struct bnxt*,struct bnxt_cp_ring_info*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_discard_rx(struct bnxt *bp, struct bnxt_cp_ring_info *cpr,
			   u32 *raw_cons, void *cmp)
{
	struct rx_cmp *rxcmp = cmp;
	u32 tmp_raw_cons = *raw_cons;
	u8 cmp_type, agg_bufs = 0;

	cmp_type = RX_CMP_TYPE(rxcmp);

	if (cmp_type == CMP_TYPE_RX_L2_CMP) {
		agg_bufs = (le32_to_cpu(rxcmp->rx_cmp_misc_v1) &
			    RX_CMP_AGG_BUFS) >>
			   RX_CMP_AGG_BUFS_SHIFT;
	} else if (cmp_type == CMP_TYPE_RX_L2_TPA_END_CMP) {
		struct rx_tpa_end_cmp *tpa_end = cmp;

		if (bp->flags & BNXT_FLAG_CHIP_P5)
			return 0;

		agg_bufs = TPA_END_AGG_BUFS(tpa_end);
	}

	if (agg_bufs) {
		if (!bnxt_agg_bufs_valid(bp, cpr, agg_bufs, &tmp_raw_cons))
			return -EBUSY;
	}
	*raw_cons = tmp_raw_cons;
	return 0;
}