#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct tbl_walk {int pasid; TYPE_3__* pasid_tbl_entry; TYPE_2__* ctx_entry; TYPE_1__* rt_entry; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct seq_file {struct tbl_walk* private; } ;
struct TYPE_6__ {int /*<<< orphan*/ * val; } ;
struct TYPE_5__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct TYPE_4__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static inline void print_tbl_walk(struct seq_file *m)
{
	struct tbl_walk *tbl_wlk = m->private;

	seq_printf(m, "%02x:%02x.%x\t0x%016llx:0x%016llx\t0x%016llx:0x%016llx\t",
		   tbl_wlk->bus, PCI_SLOT(tbl_wlk->devfn),
		   PCI_FUNC(tbl_wlk->devfn), tbl_wlk->rt_entry->hi,
		   tbl_wlk->rt_entry->lo, tbl_wlk->ctx_entry->hi,
		   tbl_wlk->ctx_entry->lo);

	/*
	 * A legacy mode DMAR doesn't support PASID, hence default it to -1
	 * indicating that it's invalid. Also, default all PASID related fields
	 * to 0.
	 */
	if (!tbl_wlk->pasid_tbl_entry)
		seq_printf(m, "%-6d\t0x%016llx:0x%016llx:0x%016llx\n", -1,
			   (u64)0, (u64)0, (u64)0);
	else
		seq_printf(m, "%-6d\t0x%016llx:0x%016llx:0x%016llx\n",
			   tbl_wlk->pasid, tbl_wlk->pasid_tbl_entry->val[2],
			   tbl_wlk->pasid_tbl_entry->val[1],
			   tbl_wlk->pasid_tbl_entry->val[0]);
}