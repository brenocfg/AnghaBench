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
struct sdma_rht_node {struct sdma_rht_node** map; } ;

/* Variables and functions */
 int HFI1_MAX_VLS_SUPPORTED ; 
 int /*<<< orphan*/  kfree (struct sdma_rht_node*) ; 

__attribute__((used)) static void sdma_rht_free(void *ptr, void *arg)
{
	struct sdma_rht_node *rht_node = ptr;
	int i;

	for (i = 0; i < HFI1_MAX_VLS_SUPPORTED; i++)
		kfree(rht_node->map[i]);

	kfree(rht_node);
}