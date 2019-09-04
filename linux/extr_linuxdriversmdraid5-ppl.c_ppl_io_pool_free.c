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
struct ppl_io_unit {int /*<<< orphan*/  header_page; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,struct ppl_io_unit*) ; 

__attribute__((used)) static void ppl_io_pool_free(void *element, void *pool_data)
{
	struct kmem_cache *kc = pool_data;
	struct ppl_io_unit *io = element;

	__free_page(io->header_page);
	kmem_cache_free(kc, io);
}