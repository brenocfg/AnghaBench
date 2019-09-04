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
struct gmap_rmap {unsigned long raddr; } ;
struct gmap {int /*<<< orphan*/  guest_table_lock; int /*<<< orphan*/  mm; struct gmap* parent; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PGSTE_VSIE_BIT ; 
 int /*<<< orphan*/  PROT_READ ; 
 unsigned long __gmap_translate (struct gmap*,unsigned long) ; 
 int /*<<< orphan*/  gmap_insert_rmap (struct gmap*,unsigned long,struct gmap_rmap*) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 int /*<<< orphan*/  gmap_pte_op_end (int /*<<< orphan*/ *) ; 
 int gmap_pte_op_fixup (struct gmap*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gmap_pte_op_walk (struct gmap*,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kfree (struct gmap_rmap*) ; 
 struct gmap_rmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ptep_force_prot (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int radix_tree_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gmap_protect_rmap(struct gmap *sg, unsigned long raddr,
			     unsigned long paddr, unsigned long len)
{
	struct gmap *parent;
	struct gmap_rmap *rmap;
	unsigned long vmaddr;
	spinlock_t *ptl;
	pte_t *ptep;
	int rc;

	BUG_ON(!gmap_is_shadow(sg));
	parent = sg->parent;
	while (len) {
		vmaddr = __gmap_translate(parent, paddr);
		if (IS_ERR_VALUE(vmaddr))
			return vmaddr;
		rmap = kzalloc(sizeof(*rmap), GFP_KERNEL);
		if (!rmap)
			return -ENOMEM;
		rmap->raddr = raddr;
		rc = radix_tree_preload(GFP_KERNEL);
		if (rc) {
			kfree(rmap);
			return rc;
		}
		rc = -EAGAIN;
		ptep = gmap_pte_op_walk(parent, paddr, &ptl);
		if (ptep) {
			spin_lock(&sg->guest_table_lock);
			rc = ptep_force_prot(parent->mm, paddr, ptep, PROT_READ,
					     PGSTE_VSIE_BIT);
			if (!rc)
				gmap_insert_rmap(sg, vmaddr, rmap);
			spin_unlock(&sg->guest_table_lock);
			gmap_pte_op_end(ptl);
		}
		radix_tree_preload_end();
		if (rc) {
			kfree(rmap);
			rc = gmap_pte_op_fixup(parent, paddr, vmaddr, PROT_READ);
			if (rc)
				return rc;
			continue;
		}
		paddr += PAGE_SIZE;
		len -= PAGE_SIZE;
	}
	return 0;
}