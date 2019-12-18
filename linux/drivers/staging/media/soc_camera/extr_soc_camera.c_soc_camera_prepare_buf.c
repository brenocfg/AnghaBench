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
struct v4l2_buffer {int dummy; } ;
struct soc_camera_device {int /*<<< orphan*/  vb2_vidq; } ;
struct file {struct soc_camera_device* private_data; } ;

/* Variables and functions */
 int vb2_prepare_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct v4l2_buffer*) ; 

__attribute__((used)) static int soc_camera_prepare_buf(struct file *file, void *priv,
				  struct v4l2_buffer *b)
{
	struct soc_camera_device *icd = file->private_data;

	return vb2_prepare_buf(&icd->vb2_vidq, NULL, b);
}