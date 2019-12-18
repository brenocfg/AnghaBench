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
struct vring_virtqueue {scalar_t__ packed_ring; } ;

/* Variables and functions */
 int more_used_packed (struct vring_virtqueue const*) ; 
 int more_used_split (struct vring_virtqueue const*) ; 

__attribute__((used)) static inline bool more_used(const struct vring_virtqueue *vq)
{
	return vq->packed_ring ? more_used_packed(vq) : more_used_split(vq);
}