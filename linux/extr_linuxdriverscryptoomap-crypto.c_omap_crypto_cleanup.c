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
typedef  unsigned long u8 ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 unsigned long OMAP_CRYPTO_COPY_MASK ; 
 unsigned long OMAP_CRYPTO_DATA_COPIED ; 
 unsigned long OMAP_CRYPTO_SG_COPIED ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (void*,struct scatterlist*,int,int,int) ; 
 void* sg_virt (struct scatterlist*) ; 

void omap_crypto_cleanup(struct scatterlist *sg, struct scatterlist *orig,
			 int offset, int len, u8 flags_shift,
			 unsigned long flags)
{
	void *buf;
	int pages;

	flags >>= flags_shift;
	flags &= OMAP_CRYPTO_COPY_MASK;

	if (!flags)
		return;

	buf = sg_virt(sg);
	pages = get_order(len);

	if (orig && (flags & OMAP_CRYPTO_COPY_MASK))
		scatterwalk_map_and_copy(buf, orig, offset, len, 1);

	if (flags & OMAP_CRYPTO_DATA_COPIED)
		free_pages((unsigned long)buf, pages);
	else if (flags & OMAP_CRYPTO_SG_COPIED)
		kfree(sg);
}