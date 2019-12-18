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
struct bnxt {int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bnxt_close_nic (struct bnxt*,int,int) ; 
 int /*<<< orphan*/  bnxt_clear_int_mode (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_ctx_mem (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_func_drv_unrgtr (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_ulp_irq_stop (struct bnxt*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_fw_reset_close(struct bnxt *bp)
{
	__bnxt_close_nic(bp, true, false);
	bnxt_ulp_irq_stop(bp);
	bnxt_clear_int_mode(bp);
	bnxt_hwrm_func_drv_unrgtr(bp);
	bnxt_free_ctx_mem(bp);
	kfree(bp->ctx);
	bp->ctx = NULL;
}