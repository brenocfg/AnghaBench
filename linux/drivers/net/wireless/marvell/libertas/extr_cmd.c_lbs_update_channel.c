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
struct lbs_private {int channel; } ;

/* Variables and functions */
 int lbs_get_channel (struct lbs_private*) ; 

int lbs_update_channel(struct lbs_private *priv)
{
	int ret;

	/* the channel in f/w could be out of sync; get the current channel */
	ret = lbs_get_channel(priv);
	if (ret > 0) {
		priv->channel = ret;
		ret = 0;
	}

	return ret;
}