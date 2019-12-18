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
typedef  int /*<<< orphan*/  uint32_t ;
struct vm_area_struct {int /*<<< orphan*/  vm_flags; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  pgprot_noncached_wc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_get_page_prot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pgprot_t drm_dma_prot(uint32_t map_type, struct vm_area_struct *vma)
{
	pgprot_t tmp = vm_get_page_prot(vma->vm_flags);

#if defined(__powerpc__) && defined(CONFIG_NOT_COHERENT_CACHE)
	tmp = pgprot_noncached_wc(tmp);
#endif
	return tmp;
}