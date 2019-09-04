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
typedef  void page ;
struct crypt_config {int /*<<< orphan*/  n_allocated_pages; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int __GFP_NORETRY ; 
 void* alloc_page (int) ; 
 int /*<<< orphan*/  dm_crypt_pages_per_client ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  percpu_counter_add (int /*<<< orphan*/ *,int) ; 
 scalar_t__ percpu_counter_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *crypt_page_alloc(gfp_t gfp_mask, void *pool_data)
{
	struct crypt_config *cc = pool_data;
	struct page *page;

	if (unlikely(percpu_counter_compare(&cc->n_allocated_pages, dm_crypt_pages_per_client) >= 0) &&
	    likely(gfp_mask & __GFP_NORETRY))
		return NULL;

	page = alloc_page(gfp_mask);
	if (likely(page != NULL))
		percpu_counter_add(&cc->n_allocated_pages, 1);

	return page;
}