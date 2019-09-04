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
struct hdpvr_fh {int legacy_mode; int /*<<< orphan*/  fh; } ;
struct file {struct hdpvr_fh* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hdpvr_fh* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 

__attribute__((used)) static int hdpvr_open(struct file *file)
{
	struct hdpvr_fh *fh = kzalloc(sizeof(*fh), GFP_KERNEL);

	if (fh == NULL)
		return -ENOMEM;
	fh->legacy_mode = true;
	v4l2_fh_init(&fh->fh, video_devdata(file));
	v4l2_fh_add(&fh->fh);
	file->private_data = fh;
	return 0;
}