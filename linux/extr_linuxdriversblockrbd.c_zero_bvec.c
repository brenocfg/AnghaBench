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
struct bio_vec {int /*<<< orphan*/  bv_page; int /*<<< orphan*/  bv_len; } ;

/* Variables and functions */
 void* bvec_kmap_irq (struct bio_vec*,unsigned long*) ; 
 int /*<<< orphan*/  bvec_kunmap_irq (void*,unsigned long*) ; 
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zero_bvec(struct bio_vec *bv)
{
	void *buf;
	unsigned long flags;

	buf = bvec_kmap_irq(bv, &flags);
	memset(buf, 0, bv->bv_len);
	flush_dcache_page(bv->bv_page);
	bvec_kunmap_irq(buf, &flags);
}