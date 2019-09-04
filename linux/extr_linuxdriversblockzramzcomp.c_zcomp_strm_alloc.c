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
struct zcomp_strm {void* buffer; int /*<<< orphan*/  tfm; } ;
struct zcomp {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int) ; 
 int /*<<< orphan*/  crypto_alloc_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct zcomp_strm* kmalloc (int,int) ; 
 int /*<<< orphan*/  zcomp_strm_free (struct zcomp_strm*) ; 

__attribute__((used)) static struct zcomp_strm *zcomp_strm_alloc(struct zcomp *comp)
{
	struct zcomp_strm *zstrm = kmalloc(sizeof(*zstrm), GFP_KERNEL);
	if (!zstrm)
		return NULL;

	zstrm->tfm = crypto_alloc_comp(comp->name, 0, 0);
	/*
	 * allocate 2 pages. 1 for compressed data, plus 1 extra for the
	 * case when compressed size is larger than the original one
	 */
	zstrm->buffer = (void *)__get_free_pages(GFP_KERNEL | __GFP_ZERO, 1);
	if (IS_ERR_OR_NULL(zstrm->tfm) || !zstrm->buffer) {
		zcomp_strm_free(zstrm);
		zstrm = NULL;
	}
	return zstrm;
}