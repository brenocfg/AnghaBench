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
struct pblk_w_ctx {int /*<<< orphan*/  lba; int /*<<< orphan*/  ppa; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EMPTY ; 
 int PBLK_SUBMITTED_ENTRY ; 
 int /*<<< orphan*/  PBLK_WRITABLE_ENTRY ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  pblk_ppa_set_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clean_wctx(struct pblk_w_ctx *w_ctx)
{
	int flags;

	flags = READ_ONCE(w_ctx->flags);
	WARN_ONCE(!(flags & PBLK_SUBMITTED_ENTRY),
			"pblk: overwriting unsubmitted data\n");

	/* Release flags on context. Protect from writes and reads */
	smp_store_release(&w_ctx->flags, PBLK_WRITABLE_ENTRY);
	pblk_ppa_set_empty(&w_ctx->ppa);
	w_ctx->lba = ADDR_EMPTY;
}