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
struct bttv_fh {struct bttv* btv; } ;
struct bttv {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  bttv_queue (struct bttv_fh*) ; 
 int bttv_resource (struct bttv_fh*) ; 
 int /*<<< orphan*/  free_btres_lock (struct bttv*,struct bttv_fh*,int) ; 
 int videobuf_streamoff (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bttv_streamoff(struct file *file, void *priv,
					enum v4l2_buf_type type)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;
	int retval;
	int res = bttv_resource(fh);


	retval = videobuf_streamoff(bttv_queue(fh));
	if (retval < 0)
		return retval;
	free_btres_lock(btv, fh, res);
	return 0;
}