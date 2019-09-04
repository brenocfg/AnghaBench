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
struct file {int dummy; } ;
struct cx231xx_fh {int /*<<< orphan*/  vb_vidq; struct cx231xx* dev; } ;
struct cx231xx {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int check_dev (struct cx231xx*) ; 
 scalar_t__ likely (int) ; 
 int res_get (struct cx231xx_fh*) ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  video ; 
 int videobuf_streamon (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamon(struct file *file, void *priv,
			   enum v4l2_buf_type type)
{
	struct cx231xx_fh *fh = priv;
	struct cx231xx *dev = fh->dev;
	int rc;

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	rc = res_get(fh);

	if (likely(rc >= 0))
		rc = videobuf_streamon(&fh->vb_vidq);

	call_all(dev, video, s_stream, 1);

	return rc;
}