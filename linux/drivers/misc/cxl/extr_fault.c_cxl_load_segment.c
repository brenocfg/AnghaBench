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
struct cxl_sste {void* esid_data; void* vsid_data; } ;
struct cxl_context {int sstp; int /*<<< orphan*/  sste_lock; } ;
struct copro_slb {int /*<<< orphan*/  esid; int /*<<< orphan*/  vsid; } ;

/* Variables and functions */
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 struct cxl_sste* find_free_sste (struct cxl_context*,struct copro_slb*) ; 
 int /*<<< orphan*/  pr_devel (char*,struct cxl_sste*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_cxl_ste_write (struct cxl_context*,struct cxl_sste*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxl_load_segment(struct cxl_context *ctx, struct copro_slb *slb)
{
	/* mask is the group index, we search primary and secondary here. */
	struct cxl_sste *sste;
	unsigned long flags;

	spin_lock_irqsave(&ctx->sste_lock, flags);
	sste = find_free_sste(ctx, slb);
	if (!sste)
		goto out_unlock;

	pr_devel("CXL Populating SST[%li]: %#llx %#llx\n",
			sste - ctx->sstp, slb->vsid, slb->esid);
	trace_cxl_ste_write(ctx, sste - ctx->sstp, slb->esid, slb->vsid);

	sste->vsid_data = cpu_to_be64(slb->vsid);
	sste->esid_data = cpu_to_be64(slb->esid);
out_unlock:
	spin_unlock_irqrestore(&ctx->sste_lock, flags);
}