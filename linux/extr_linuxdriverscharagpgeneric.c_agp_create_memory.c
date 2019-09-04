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
struct agp_memory {scalar_t__ key; int num_scratch_pages; int /*<<< orphan*/  type; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_NORMAL_MEMORY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  agp_alloc_page_array (int,struct agp_memory*) ; 
 int /*<<< orphan*/  agp_free_key (scalar_t__) ; 
 scalar_t__ agp_get_key () ; 
 int /*<<< orphan*/  kfree (struct agp_memory*) ; 
 struct agp_memory* kzalloc (int,int /*<<< orphan*/ ) ; 

struct agp_memory *agp_create_memory(int scratch_pages)
{
	struct agp_memory *new;

	new = kzalloc(sizeof(struct agp_memory), GFP_KERNEL);
	if (new == NULL)
		return NULL;

	new->key = agp_get_key();

	if (new->key < 0) {
		kfree(new);
		return NULL;
	}

	agp_alloc_page_array(PAGE_SIZE * scratch_pages, new);

	if (new->pages == NULL) {
		agp_free_key(new->key);
		kfree(new);
		return NULL;
	}
	new->num_scratch_pages = scratch_pages;
	new->type = AGP_NORMAL_MEMORY;
	return new;
}