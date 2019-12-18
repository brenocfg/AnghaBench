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
struct vchiu_queue {scalar_t__ read; scalar_t__ write; } ;

/* Variables and functions */

int vchiu_queue_is_empty(struct vchiu_queue *queue)
{
	return queue->read == queue->write;
}