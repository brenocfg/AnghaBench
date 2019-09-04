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
struct hfi1_affinity_node {int /*<<< orphan*/  comp_vect_affinity; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hfi1_affinity_node*) ; 

__attribute__((used)) static void node_affinity_destroy(struct hfi1_affinity_node *entry)
{
	free_percpu(entry->comp_vect_affinity);
	kfree(entry);
}