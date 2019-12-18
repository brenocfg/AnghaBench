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
struct v4l2_frequency_band {int dummy; } ;
struct file {int dummy; } ;
struct bttv_fh {struct bttv* btv; } ;
struct bttv {int /*<<< orphan*/  tea; scalar_t__ has_tea575x; } ;

/* Variables and functions */
 int ENOTTY ; 
 int snd_tea575x_enum_freq_bands (int /*<<< orphan*/ *,struct v4l2_frequency_band*) ; 

__attribute__((used)) static int radio_enum_freq_bands(struct file *file, void *priv,
					 struct v4l2_frequency_band *band)
{
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;

	if (btv->has_tea575x)
		return snd_tea575x_enum_freq_bands(&btv->tea, band);

	return -ENOTTY;
}