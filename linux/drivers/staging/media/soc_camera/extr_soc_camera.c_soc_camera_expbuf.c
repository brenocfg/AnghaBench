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
struct v4l2_exportbuffer {int dummy; } ;
struct soc_camera_device {int /*<<< orphan*/  vb2_vidq; struct file* streamer; } ;
struct file {struct soc_camera_device* private_data; } ;

/* Variables and functions */
 int EBUSY ; 
 int vb2_expbuf (int /*<<< orphan*/ *,struct v4l2_exportbuffer*) ; 

__attribute__((used)) static int soc_camera_expbuf(struct file *file, void *priv,
			     struct v4l2_exportbuffer *p)
{
	struct soc_camera_device *icd = file->private_data;

	if (icd->streamer && icd->streamer != file)
		return -EBUSY;
	return vb2_expbuf(&icd->vb2_vidq, p);
}