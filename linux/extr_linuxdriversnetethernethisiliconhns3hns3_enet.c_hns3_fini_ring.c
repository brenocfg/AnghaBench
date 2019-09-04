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
struct hns3_enet_ring {scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/ * desc_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_free_desc (struct hns3_enet_ring*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns3_fini_ring(struct hns3_enet_ring *ring)
{
	hns3_free_desc(ring);
	kfree(ring->desc_cb);
	ring->desc_cb = NULL;
	ring->next_to_clean = 0;
	ring->next_to_use = 0;
}