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
struct bnxt_cp_ring_info {int /*<<< orphan*/ ** cp_desc_ring; int /*<<< orphan*/  event_ctr; int /*<<< orphan*/  cp_raw_cons; } ;
struct bnxt_napi {int /*<<< orphan*/  napi; struct bnxt_cp_ring_info cp_ring; struct bnxt* bp; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t CP_IDX (int /*<<< orphan*/ ) ; 
 size_t CP_RING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RING_CMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bnxt_msix(int irq, void *dev_instance)
{
	struct bnxt_napi *bnapi = dev_instance;
	struct bnxt *bp = bnapi->bp;
	struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	u32 cons = RING_CMP(cpr->cp_raw_cons);

	cpr->event_ctr++;
	prefetch(&cpr->cp_desc_ring[CP_RING(cons)][CP_IDX(cons)]);
	napi_schedule(&bnapi->napi);
	return IRQ_HANDLED;
}