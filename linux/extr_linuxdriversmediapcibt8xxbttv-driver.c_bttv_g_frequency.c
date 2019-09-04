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
struct v4l2_frequency {scalar_t__ type; int /*<<< orphan*/  frequency; scalar_t__ tuner; } ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {int /*<<< orphan*/  tv_freq; int /*<<< orphan*/  radio_freq; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  radio_enable (struct bttv*) ; 

__attribute__((used)) static int bttv_g_frequency(struct file *file, void *priv,
					struct v4l2_frequency *f)
{
	struct bttv_fh *fh  = priv;
	struct bttv *btv = fh->btv;

	if (f->tuner)
		return -EINVAL;

	if (f->type == V4L2_TUNER_RADIO)
		radio_enable(btv);
	f->frequency = f->type == V4L2_TUNER_RADIO ?
				btv->radio_freq : btv->tv_freq;

	return 0;
}