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
struct TYPE_3__ {int qual; int level; int /*<<< orphan*/  updated; } ;
struct TYPE_4__ {TYPE_1__ qual; } ;
struct atmel_private {unsigned long last_qual; int beacons_this_sec; int beacon_period; TYPE_2__ wstats; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  IW_QUAL_QUAL_INVALID ; 
 int /*<<< orphan*/  IW_QUAL_QUAL_UPDATED ; 
 unsigned long jiffies ; 

__attribute__((used)) static void atmel_smooth_qual(struct atmel_private *priv)
{
	unsigned long time_diff = (jiffies - priv->last_qual) / HZ;
	while (time_diff--) {
		priv->last_qual += HZ;
		priv->wstats.qual.qual = priv->wstats.qual.qual / 2;
		priv->wstats.qual.qual +=
			priv->beacons_this_sec * priv->beacon_period * (priv->wstats.qual.level + 100) / 4000;
		priv->beacons_this_sec = 0;
	}
	priv->wstats.qual.updated |= IW_QUAL_QUAL_UPDATED;
	priv->wstats.qual.updated &= ~IW_QUAL_QUAL_INVALID;
}