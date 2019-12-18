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
struct timer_list {int dummy; } ;
struct saa7146_vv {struct file* vbi_read_timeout_file; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {int dummy; } ;
struct file {struct saa7146_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_VBI (char*,struct saa7146_dev*,struct saa7146_fh*) ; 
 struct saa7146_vv* from_timer (int /*<<< orphan*/ ,struct timer_list*,void (*) (struct timer_list*)) ; 
 int /*<<< orphan*/  vbi_stop (struct saa7146_fh*,struct file*) ; 
 struct saa7146_vv* vv ; 

__attribute__((used)) static void vbi_read_timeout(struct timer_list *t)
{
	struct saa7146_vv *vv = from_timer(vv, t, vbi_read_timeout);
	struct file *file = vv->vbi_read_timeout_file;
	struct saa7146_fh *fh = file->private_data;
	struct saa7146_dev *dev = fh->dev;

	DEB_VBI("dev:%p, fh:%p\n", dev, fh);

	vbi_stop(fh, file);
}