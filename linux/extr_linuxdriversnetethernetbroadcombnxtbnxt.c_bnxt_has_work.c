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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tx_cmp {int dummy; } ;
struct bnxt_cp_ring_info {struct tx_cmp** cp_desc_ring; int /*<<< orphan*/  cp_raw_cons; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 size_t CP_IDX (int /*<<< orphan*/ ) ; 
 size_t CP_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RING_CMP (int /*<<< orphan*/ ) ; 
 int TX_CMP_VALID (struct tx_cmp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bnxt_has_work(struct bnxt *bp, struct bnxt_cp_ring_info *cpr)
{
	u32 raw_cons = cpr->cp_raw_cons;
	u16 cons = RING_CMP(raw_cons);
	struct tx_cmp *txcmp;

	txcmp = &cpr->cp_desc_ring[CP_RING(cons)][CP_IDX(cons)];

	return TX_CMP_VALID(txcmp, raw_cons);
}