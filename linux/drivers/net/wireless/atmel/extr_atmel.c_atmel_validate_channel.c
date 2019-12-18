#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct atmel_private {scalar_t__ reg_domain; } ;
struct TYPE_3__ {scalar_t__ reg_domain; int min; int max; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* channel_table ; 

__attribute__((used)) static int atmel_validate_channel(struct atmel_private *priv, int channel)
{
	/* check that channel is OK, if so return zero,
	   else return suitable default channel */
	int i;

	for (i = 0; i < ARRAY_SIZE(channel_table); i++)
		if (priv->reg_domain == channel_table[i].reg_domain) {
			if (channel >= channel_table[i].min &&
			    channel <= channel_table[i].max)
				return 0;
			else
				return channel_table[i].min;
		}
	return 0;
}