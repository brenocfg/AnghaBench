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
struct ubi_attach_info {int /*<<< orphan*/  aeb_slab_cache; } ;
struct ubi_ainf_peb {int pnum; int ec; void* lnum; void* vol_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* UBI_UNKNOWN ; 
 struct ubi_ainf_peb* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ubi_ainf_peb *ubi_alloc_aeb(struct ubi_attach_info *ai, int pnum,
				   int ec)
{
	struct ubi_ainf_peb *aeb;

	aeb = kmem_cache_zalloc(ai->aeb_slab_cache, GFP_KERNEL);
	if (!aeb)
		return NULL;

	aeb->pnum = pnum;
	aeb->ec = ec;
	aeb->vol_id = UBI_UNKNOWN;
	aeb->lnum = UBI_UNKNOWN;

	return aeb;
}