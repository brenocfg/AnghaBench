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
typedef  int u16 ;
struct vring_virtqueue {int dummy; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int VRING_PACKED_EVENT_F_WRAP_CTR ; 
 int is_used_desc_packed (struct vring_virtqueue*,int,int) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 

__attribute__((used)) static bool virtqueue_poll_packed(struct virtqueue *_vq, u16 off_wrap)
{
	struct vring_virtqueue *vq = to_vvq(_vq);
	bool wrap_counter;
	u16 used_idx;

	wrap_counter = off_wrap >> VRING_PACKED_EVENT_F_WRAP_CTR;
	used_idx = off_wrap & ~(1 << VRING_PACKED_EVENT_F_WRAP_CTR);

	return is_used_desc_packed(vq, used_idx, wrap_counter);
}