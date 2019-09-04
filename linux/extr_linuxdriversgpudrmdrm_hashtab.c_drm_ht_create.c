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
struct drm_open_hash {unsigned int order; int /*<<< orphan*/ * table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  array_size (unsigned int,int) ; 
 int /*<<< orphan*/ * kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vzalloc (int /*<<< orphan*/ ) ; 

int drm_ht_create(struct drm_open_hash *ht, unsigned int order)
{
	unsigned int size = 1 << order;

	ht->order = order;
	ht->table = NULL;
	if (size <= PAGE_SIZE / sizeof(*ht->table))
		ht->table = kcalloc(size, sizeof(*ht->table), GFP_KERNEL);
	else
		ht->table = vzalloc(array_size(size, sizeof(*ht->table)));
	if (!ht->table) {
		DRM_ERROR("Out of memory for hash table\n");
		return -ENOMEM;
	}
	return 0;
}