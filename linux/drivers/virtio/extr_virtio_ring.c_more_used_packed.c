#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  used_wrap_counter; } ;
struct vring_virtqueue {TYPE_1__ packed; int /*<<< orphan*/  last_used_idx; } ;

/* Variables and functions */
 int is_used_desc_packed (struct vring_virtqueue const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool more_used_packed(const struct vring_virtqueue *vq)
{
	return is_used_desc_packed(vq, vq->last_used_idx,
			vq->packed.used_wrap_counter);
}