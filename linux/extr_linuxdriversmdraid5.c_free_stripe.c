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
struct stripe_head {scalar_t__ ppl_page; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,struct stripe_head*) ; 

__attribute__((used)) static void free_stripe(struct kmem_cache *sc, struct stripe_head *sh)
{
	if (sh->ppl_page)
		__free_page(sh->ppl_page);
	kmem_cache_free(sc, sh);
}