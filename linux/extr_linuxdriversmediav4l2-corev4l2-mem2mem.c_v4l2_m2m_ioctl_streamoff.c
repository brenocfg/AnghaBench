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
struct v4l2_fh {int /*<<< orphan*/  m2m_ctx; } ;
struct file {struct v4l2_fh* private_data; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int v4l2_m2m_streamoff (struct file*,int /*<<< orphan*/ ,int) ; 

int v4l2_m2m_ioctl_streamoff(struct file *file, void *priv,
				enum v4l2_buf_type type)
{
	struct v4l2_fh *fh = file->private_data;

	return v4l2_m2m_streamoff(file, fh->m2m_ctx, type);
}