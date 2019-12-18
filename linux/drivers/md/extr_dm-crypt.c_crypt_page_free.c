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
struct crypt_config {int /*<<< orphan*/  n_allocated_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (void*) ; 
 int /*<<< orphan*/  percpu_counter_sub (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void crypt_page_free(void *page, void *pool_data)
{
	struct crypt_config *cc = pool_data;

	__free_page(page);
	percpu_counter_sub(&cc->n_allocated_pages, 1);
}