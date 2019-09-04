#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int v4l2_std_id ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {int std; } ;
struct TYPE_2__ {int v4l2_id; } ;

/* Variables and functions */
 unsigned int BTTV_TVNORMS ; 
 int EINVAL ; 
 TYPE_1__* bttv_tvnorms ; 
 int /*<<< orphan*/  set_tvnorm (struct bttv*,unsigned int) ; 

__attribute__((used)) static int bttv_s_std(struct file *file, void *priv, v4l2_std_id id)
{
	struct bttv_fh *fh  = priv;
	struct bttv *btv = fh->btv;
	unsigned int i;

	for (i = 0; i < BTTV_TVNORMS; i++)
		if (id & bttv_tvnorms[i].v4l2_id)
			break;
	if (i == BTTV_TVNORMS)
		return -EINVAL;
	btv->std = id;
	set_tvnorm(btv, i);
	return 0;
}