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
struct ubi_ainf_peb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ubi_ainf_peb*) ; 

void ubi_free_aeb(struct ubi_attach_info *ai, struct ubi_ainf_peb *aeb)
{
	kmem_cache_free(ai->aeb_slab_cache, aeb);
}