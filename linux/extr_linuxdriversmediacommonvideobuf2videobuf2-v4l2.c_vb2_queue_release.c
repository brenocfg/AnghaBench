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
struct vb2_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vb2_core_queue_release (struct vb2_queue*) ; 

void vb2_queue_release(struct vb2_queue *q)
{
	vb2_core_queue_release(q);
}