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
struct v4l2_format {int dummy; } ;
struct solo_dev {int /*<<< orphan*/  vidq; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int solo_try_fmt_cap (struct file*,void*,struct v4l2_format*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct solo_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int solo_set_fmt_cap(struct file *file, void *priv,
			    struct v4l2_format *f)
{
	struct solo_dev *solo_dev = video_drvdata(file);

	if (vb2_is_busy(&solo_dev->vidq))
		return -EBUSY;

	/* For right now, if it doesn't match our running config,
	 * then fail */
	return solo_try_fmt_cap(file, priv, f);
}