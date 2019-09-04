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
 int EBUSY ; 
 int /*<<< orphan*/  bttv_queue (struct bttv_fh*) ; 
 int bttv_resource (struct bttv_fh*) ; 
 int /*<<< orphan*/  check_alloc_btres_lock (struct bttv*,struct bttv_fh*,int) ; 
 int videobuf_streamon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bttv_streamon(struct file *file, void *priv,
					enum v4l2_buf_type type)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;
	int res = bttv_resource(fh);

	if (!check_alloc_btres_lock(btv, fh, res))
		return -EBUSY;
	return videobuf_streamon(bttv_queue(fh));
}