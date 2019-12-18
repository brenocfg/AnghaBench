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
struct vb2_queue {int io_modes; scalar_t__ supports_requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_BUF_CAP_SUPPORTS_DMABUF ; 
 int /*<<< orphan*/  V4L2_BUF_CAP_SUPPORTS_MMAP ; 
 int /*<<< orphan*/  V4L2_BUF_CAP_SUPPORTS_ORPHANED_BUFS ; 
 int /*<<< orphan*/  V4L2_BUF_CAP_SUPPORTS_REQUESTS ; 
 int /*<<< orphan*/  V4L2_BUF_CAP_SUPPORTS_USERPTR ; 
 int VB2_DMABUF ; 
 int VB2_MMAP ; 
 int VB2_USERPTR ; 

__attribute__((used)) static void fill_buf_caps(struct vb2_queue *q, u32 *caps)
{
	*caps = V4L2_BUF_CAP_SUPPORTS_ORPHANED_BUFS;
	if (q->io_modes & VB2_MMAP)
		*caps |= V4L2_BUF_CAP_SUPPORTS_MMAP;
	if (q->io_modes & VB2_USERPTR)
		*caps |= V4L2_BUF_CAP_SUPPORTS_USERPTR;
	if (q->io_modes & VB2_DMABUF)
		*caps |= V4L2_BUF_CAP_SUPPORTS_DMABUF;
#ifdef CONFIG_MEDIA_CONTROLLER_REQUEST_API
	if (q->supports_requests)
		*caps |= V4L2_BUF_CAP_SUPPORTS_REQUESTS;
#endif
}