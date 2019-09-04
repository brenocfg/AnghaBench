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
struct gmap {int /*<<< orphan*/  mm; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 unsigned long GMAP_NOTIFY_MPROT ; 
 unsigned long GMAP_NOTIFY_SHADOW ; 
 unsigned long PGSTE_IN_BIT ; 
 unsigned long PGSTE_VSIE_BIT ; 
 int _SEGMENT_ENTRY_INVALID ; 
 int /*<<< orphan*/  gmap_pte_op_end (int /*<<< orphan*/ *) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_alloc_map_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 int ptep_force_prot (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int,unsigned long) ; 

__attribute__((used)) static int gmap_protect_pte(struct gmap *gmap, unsigned long gaddr,
			    pmd_t *pmdp, int prot, unsigned long bits)
{
	int rc;
	pte_t *ptep;
	spinlock_t *ptl = NULL;
	unsigned long pbits = 0;

	if (pmd_val(*pmdp) & _SEGMENT_ENTRY_INVALID)
		return -EAGAIN;

	ptep = pte_alloc_map_lock(gmap->mm, pmdp, gaddr, &ptl);
	if (!ptep)
		return -ENOMEM;

	pbits |= (bits & GMAP_NOTIFY_MPROT) ? PGSTE_IN_BIT : 0;
	pbits |= (bits & GMAP_NOTIFY_SHADOW) ? PGSTE_VSIE_BIT : 0;
	/* Protect and unlock. */
	rc = ptep_force_prot(gmap->mm, gaddr, ptep, prot, pbits);
	gmap_pte_op_end(ptl);
	return rc;
}