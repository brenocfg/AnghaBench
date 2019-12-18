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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  doorbell; } ;
struct TYPE_3__ {int fw_ring_id; } ;
struct bnxt_cp_ring_info {TYPE_2__ cp_db; TYPE_1__ cp_ring_struct; int /*<<< orphan*/ ** cp_desc_ring; int /*<<< orphan*/  cp_raw_cons; } ;
struct bnxt_napi {int /*<<< orphan*/  napi; struct bnxt_cp_ring_info cp_ring; struct bnxt* bp; } ;
struct bnxt {int /*<<< orphan*/  intr_sem; scalar_t__ bar0; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ BNXT_CAG_REG_LEGACY_INT_STATUS ; 
 int /*<<< orphan*/  BNXT_CP_DB_IRQ_DIS (int /*<<< orphan*/ ) ; 
 size_t CP_IDX (int) ; 
 size_t CP_RING (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RING_CMP (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_has_work (struct bnxt*,struct bnxt_cp_ring_info*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t bnxt_inta(int irq, void *dev_instance)
{
	struct bnxt_napi *bnapi = dev_instance;
	struct bnxt *bp = bnapi->bp;
	struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	u32 cons = RING_CMP(cpr->cp_raw_cons);
	u32 int_status;

	prefetch(&cpr->cp_desc_ring[CP_RING(cons)][CP_IDX(cons)]);

	if (!bnxt_has_work(bp, cpr)) {
		int_status = readl(bp->bar0 + BNXT_CAG_REG_LEGACY_INT_STATUS);
		/* return if erroneous interrupt */
		if (!(int_status & (0x10000 << cpr->cp_ring_struct.fw_ring_id)))
			return IRQ_NONE;
	}

	/* disable ring IRQ */
	BNXT_CP_DB_IRQ_DIS(cpr->cp_db.doorbell);

	/* Return here if interrupt is shared and is disabled. */
	if (unlikely(atomic_read(&bp->intr_sem) != 0))
		return IRQ_HANDLED;

	napi_schedule(&bnapi->napi);
	return IRQ_HANDLED;
}