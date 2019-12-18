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
struct v4l2_frequency {scalar_t__ tuner; } ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bttv_set_frequency (struct bttv*,struct v4l2_frequency const*) ; 

__attribute__((used)) static int bttv_s_frequency(struct file *file, void *priv,
					const struct v4l2_frequency *f)
{
	struct bttv_fh *fh  = priv;
	struct bttv *btv = fh->btv;

	if (f->tuner)
		return -EINVAL;

	bttv_set_frequency(btv, f);
	return 0;
}