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
struct hclge_cmq_ring {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_free_cmd_desc (struct hclge_cmq_ring*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_destroy_queue(struct hclge_cmq_ring *ring)
{
	spin_lock(&ring->lock);
	hclge_free_cmd_desc(ring);
	spin_unlock(&ring->lock);
}