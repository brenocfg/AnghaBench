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
struct gmap {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EINVAL ; 
 unsigned long HPAGE_MASK ; 
 unsigned long HPAGE_SIZE ; 
 scalar_t__ IS_ERR_VALUE (unsigned long) ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long __gmap_translate (struct gmap*,unsigned long) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 int /*<<< orphan*/  gmap_pmd_op_end (struct gmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gmap_pmd_op_walk (struct gmap*,unsigned long) ; 
 int gmap_protect_pmd (struct gmap*,unsigned long,int /*<<< orphan*/ *,int,unsigned long) ; 
 int gmap_protect_pte (struct gmap*,unsigned long,int /*<<< orphan*/ *,int,unsigned long) ; 
 int gmap_pte_op_fixup (struct gmap*,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  pmd_large (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gmap_protect_range(struct gmap *gmap, unsigned long gaddr,
			      unsigned long len, int prot, unsigned long bits)
{
	unsigned long vmaddr, dist;
	pmd_t *pmdp;
	int rc;

	BUG_ON(gmap_is_shadow(gmap));
	while (len) {
		rc = -EAGAIN;
		pmdp = gmap_pmd_op_walk(gmap, gaddr);
		if (pmdp) {
			if (!pmd_large(*pmdp)) {
				rc = gmap_protect_pte(gmap, gaddr, pmdp, prot,
						      bits);
				if (!rc) {
					len -= PAGE_SIZE;
					gaddr += PAGE_SIZE;
				}
			} else {
				rc = gmap_protect_pmd(gmap, gaddr, pmdp, prot,
						      bits);
				if (!rc) {
					dist = HPAGE_SIZE - (gaddr & ~HPAGE_MASK);
					len = len < dist ? 0 : len - dist;
					gaddr = (gaddr & HPAGE_MASK) + HPAGE_SIZE;
				}
			}
			gmap_pmd_op_end(gmap, pmdp);
		}
		if (rc) {
			if (rc == -EINVAL)
				return rc;

			/* -EAGAIN, fixup of userspace mm and gmap */
			vmaddr = __gmap_translate(gmap, gaddr);
			if (IS_ERR_VALUE(vmaddr))
				return vmaddr;
			rc = gmap_pte_op_fixup(gmap, gaddr, vmaddr, prot);
			if (rc)
				return rc;
		}
	}
	return 0;
}