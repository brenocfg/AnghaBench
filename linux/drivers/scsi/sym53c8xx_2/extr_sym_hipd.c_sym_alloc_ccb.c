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
struct sym_hcb {scalar_t__ actccbs; int /*<<< orphan*/  dummy_ccbq; int /*<<< orphan*/  free_ccbq; struct sym_ccb** ccbh; } ;
struct TYPE_7__ {void* addr; } ;
struct TYPE_5__ {void* restart; void* start; } ;
struct TYPE_6__ {TYPE_1__ go; } ;
struct TYPE_8__ {TYPE_3__ smsg_ext; TYPE_2__ head; } ;
struct sym_ccb {int /*<<< orphan*/  link2_ccbq; int /*<<< orphan*/  link_ccbq; TYPE_4__ phys; struct sym_ccb* link_ccbh; int /*<<< orphan*/  ccb_ba; } ;

/* Variables and functions */
 int CCB_HASH_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCB_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTA_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTB_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ SYM_CONF_MAX_START ; 
 int /*<<< orphan*/  bad_i_t_l ; 
 void* cpu_to_scr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idle ; 
 int /*<<< orphan*/ * msgin ; 
 struct sym_ccb* sym_calloc_dma (int,char*) ; 
 int /*<<< orphan*/  sym_insque_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_mfree_dma (struct sym_ccb*,int,char*) ; 
 int /*<<< orphan*/  vtobus (struct sym_ccb*) ; 

__attribute__((used)) static struct sym_ccb *sym_alloc_ccb(struct sym_hcb *np)
{
	struct sym_ccb *cp = NULL;
	int hcode;

	/*
	 *  Prevent from allocating more CCBs than we can 
	 *  queue to the controller.
	 */
	if (np->actccbs >= SYM_CONF_MAX_START)
		return NULL;

	/*
	 *  Allocate memory for this CCB.
	 */
	cp = sym_calloc_dma(sizeof(struct sym_ccb), "CCB");
	if (!cp)
		goto out_free;

	/*
	 *  Count it.
	 */
	np->actccbs++;

	/*
	 *  Compute the bus address of this ccb.
	 */
	cp->ccb_ba = vtobus(cp);

	/*
	 *  Insert this ccb into the hashed list.
	 */
	hcode = CCB_HASH_CODE(cp->ccb_ba);
	cp->link_ccbh = np->ccbh[hcode];
	np->ccbh[hcode] = cp;

	/*
	 *  Initialyze the start and restart actions.
	 */
	cp->phys.head.go.start   = cpu_to_scr(SCRIPTA_BA(np, idle));
	cp->phys.head.go.restart = cpu_to_scr(SCRIPTB_BA(np, bad_i_t_l));

 	/*
	 *  Initilialyze some other fields.
	 */
	cp->phys.smsg_ext.addr = cpu_to_scr(HCB_BA(np, msgin[2]));

	/*
	 *  Chain into free ccb queue.
	 */
	sym_insque_head(&cp->link_ccbq, &np->free_ccbq);

	/*
	 *  Chain into optionnal lists.
	 */
#ifdef SYM_OPT_HANDLE_DEVICE_QUEUEING
	sym_insque_head(&cp->link2_ccbq, &np->dummy_ccbq);
#endif
	return cp;
out_free:
	if (cp)
		sym_mfree_dma(cp, sizeof(*cp), "CCB");
	return NULL;
}