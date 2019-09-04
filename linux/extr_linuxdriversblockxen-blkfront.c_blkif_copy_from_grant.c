#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct copy_from_grant {size_t grant_idx; scalar_t__ bvec_offset; scalar_t__ bvec_data; struct blk_shadow* s; } ;
struct blk_shadow {TYPE_1__** grants_used; } ;
struct TYPE_2__ {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 char* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,unsigned int) ; 

__attribute__((used)) static void blkif_copy_from_grant(unsigned long gfn, unsigned int offset,
				  unsigned int len, void *data)
{
	struct copy_from_grant *info = data;
	char *shared_data;
	/* Convenient aliases */
	const struct blk_shadow *s = info->s;

	shared_data = kmap_atomic(s->grants_used[info->grant_idx]->page);

	memcpy(info->bvec_data + info->bvec_offset,
	       shared_data + offset, len);

	info->bvec_offset += len;
	info->grant_idx++;

	kunmap_atomic(shared_data);
}