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
typedef  int /*<<< orphan*/  u32 ;
struct vhost_virtqueue {int dummy; } ;
typedef  int /*<<< orphan*/  __virtio32 ;

/* Variables and functions */
 int /*<<< orphan*/  __virtio32_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_is_little_endian (struct vhost_virtqueue*) ; 

__attribute__((used)) static inline u32 vhost32_to_cpu(struct vhost_virtqueue *vq, __virtio32 val)
{
	return __virtio32_to_cpu(vhost_is_little_endian(vq), val);
}