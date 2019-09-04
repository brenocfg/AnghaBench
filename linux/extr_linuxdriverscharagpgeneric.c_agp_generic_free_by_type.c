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
struct agp_memory {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  agp_free_key (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_free_page_array (struct agp_memory*) ; 
 int /*<<< orphan*/  kfree (struct agp_memory*) ; 

void agp_generic_free_by_type(struct agp_memory *curr)
{
	agp_free_page_array(curr);
	agp_free_key(curr->key);
	kfree(curr);
}