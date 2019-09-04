#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct TYPE_3__ {size_t type; } ;
struct bttv {int /*<<< orphan*/  tvnorm; TYPE_1__ c; } ;
struct TYPE_4__ {unsigned int video_inputs; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* bttv_tvcards ; 
 int /*<<< orphan*/  set_input (struct bttv*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bttv_s_input(struct file *file, void *priv, unsigned int i)
{
	struct bttv_fh *fh  = priv;
	struct bttv *btv = fh->btv;

	if (i >= bttv_tvcards[btv->c.type].video_inputs)
		return -EINVAL;

	set_input(btv, i, btv->tvnorm);
	return 0;
}