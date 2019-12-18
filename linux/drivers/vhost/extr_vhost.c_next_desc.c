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
struct vring_desc {int flags; int /*<<< orphan*/  next; } ;
struct vhost_virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VRING_DESC_F_NEXT ; 
 int cpu_to_vhost16 (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 
 unsigned int vhost16_to_cpu (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned next_desc(struct vhost_virtqueue *vq, struct vring_desc *desc)
{
	unsigned int next;

	/* If this descriptor says it doesn't chain, we're done. */
	if (!(desc->flags & cpu_to_vhost16(vq, VRING_DESC_F_NEXT)))
		return -1U;

	/* Check they're not leading us off end of descriptors. */
	next = vhost16_to_cpu(vq, READ_ONCE(desc->next));
	return next;
}