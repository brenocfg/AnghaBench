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
typedef  scalar_t__ u8 ;
struct lbtf_private {scalar_t__ regioncode; TYPE_1__* channels; } ;
struct channel_range {scalar_t__ regdomain; scalar_t__ start; scalar_t__ end; } ;
struct TYPE_2__ {scalar_t__ flags; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct channel_range*) ; 
 size_t CHAN_TO_IDX (scalar_t__) ; 
 struct channel_range* channel_ranges ; 

__attribute__((used)) static void lbtf_geo_init(struct lbtf_private *priv)
{
	const struct channel_range *range = channel_ranges;
	u8 ch;
	int i;

	for (i = 0; i < ARRAY_SIZE(channel_ranges); i++)
		if (channel_ranges[i].regdomain == priv->regioncode) {
			range = &channel_ranges[i];
			break;
		}

	for (ch = range->start; ch < range->end; ch++)
		priv->channels[CHAN_TO_IDX(ch)].flags = 0;
}