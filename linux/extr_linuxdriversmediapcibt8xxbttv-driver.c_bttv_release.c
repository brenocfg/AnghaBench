#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct file {struct bttv_fh* private_data; } ;
struct TYPE_5__ {struct bttv_fh* read_buf; } ;
struct bttv_fh {int /*<<< orphan*/  fh; TYPE_1__ vbi; TYPE_1__ cap; struct bttv* btv; } ;
struct bttv {int /*<<< orphan*/  mute; int /*<<< orphan*/  users; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOURCE_OVERLAY ; 
 int /*<<< orphan*/  RESOURCE_VBI ; 
 int /*<<< orphan*/  RESOURCE_VIDEO_READ ; 
 int /*<<< orphan*/  RESOURCE_VIDEO_STREAM ; 
 int /*<<< orphan*/  audio_mute (struct bttv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bttv_field_count (struct bttv*) ; 
 int /*<<< orphan*/  bttv_switch_overlay (struct bttv*,struct bttv_fh*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_release (TYPE_1__*,struct bttv_fh*) ; 
 scalar_t__ check_btres (struct bttv_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_btres_lock (struct bttv*,struct bttv_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bttv_fh*) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_mmap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  videobuf_streamoff (TYPE_1__*) ; 

__attribute__((used)) static int bttv_release(struct file *file)
{
	struct bttv_fh *fh = file->private_data;
	struct bttv *btv = fh->btv;

	/* turn off overlay */
	if (check_btres(fh, RESOURCE_OVERLAY))
		bttv_switch_overlay(btv,fh,NULL);

	/* stop video capture */
	if (check_btres(fh, RESOURCE_VIDEO_STREAM)) {
		videobuf_streamoff(&fh->cap);
		free_btres_lock(btv,fh,RESOURCE_VIDEO_STREAM);
	}
	if (fh->cap.read_buf) {
		buffer_release(&fh->cap,fh->cap.read_buf);
		kfree(fh->cap.read_buf);
	}
	if (check_btres(fh, RESOURCE_VIDEO_READ)) {
		free_btres_lock(btv, fh, RESOURCE_VIDEO_READ);
	}

	/* stop vbi capture */
	if (check_btres(fh, RESOURCE_VBI)) {
		videobuf_stop(&fh->vbi);
		free_btres_lock(btv,fh,RESOURCE_VBI);
	}

	/* free stuff */

	videobuf_mmap_free(&fh->cap);
	videobuf_mmap_free(&fh->vbi);
	file->private_data = NULL;

	btv->users--;
	bttv_field_count(btv);

	if (!btv->users)
		audio_mute(btv, btv->mute);

	v4l2_fh_del(&fh->fh);
	v4l2_fh_exit(&fh->fh);
	kfree(fh);
	return 0;
}