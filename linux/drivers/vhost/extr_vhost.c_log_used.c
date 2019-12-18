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
typedef  scalar_t__ u64 ;
struct vhost_virtqueue {scalar_t__ used; scalar_t__ log_addr; int /*<<< orphan*/  log_base; int /*<<< orphan*/  iotlb; } ;
struct iovec {int /*<<< orphan*/  iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHOST_ACCESS_WO ; 
 int log_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int log_write_hva (struct vhost_virtqueue*,uintptr_t,int /*<<< orphan*/ ) ; 
 int translate_desc (struct vhost_virtqueue*,scalar_t__,scalar_t__,struct iovec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int log_used(struct vhost_virtqueue *vq, u64 used_offset, u64 len)
{
	struct iovec iov[64];
	int i, ret;

	if (!vq->iotlb)
		return log_write(vq->log_base, vq->log_addr + used_offset, len);

	ret = translate_desc(vq, (uintptr_t)vq->used + used_offset,
			     len, iov, 64, VHOST_ACCESS_WO);
	if (ret < 0)
		return ret;

	for (i = 0; i < ret; i++) {
		ret = log_write_hva(vq,	(uintptr_t)iov[i].iov_base,
				    iov[i].iov_len);
		if (ret)
			return ret;
	}

	return 0;
}