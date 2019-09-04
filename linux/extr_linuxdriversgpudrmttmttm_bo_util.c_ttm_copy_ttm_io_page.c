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
struct ttm_tt {struct page** pages; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy_toio (void*,void*,int /*<<< orphan*/ ) ; 
 void* ttm_kmap_atomic_prot (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_kunmap_atomic_prot (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttm_copy_ttm_io_page(struct ttm_tt *ttm, void *dst,
				unsigned long page,
				pgprot_t prot)
{
	struct page *s = ttm->pages[page];
	void *src;

	if (!s)
		return -ENOMEM;

	dst = (void *)((unsigned long)dst + (page << PAGE_SHIFT));
	src = ttm_kmap_atomic_prot(s, prot);
	if (!src)
		return -ENOMEM;

	memcpy_toio(dst, src, PAGE_SIZE);

	ttm_kunmap_atomic_prot(src, prot);

	return 0;
}