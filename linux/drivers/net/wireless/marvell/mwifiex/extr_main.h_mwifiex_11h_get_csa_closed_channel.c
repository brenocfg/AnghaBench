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
typedef  scalar_t__ u8 ;
struct mwifiex_private {scalar_t__ csa_chan; scalar_t__ csa_expire_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u8
mwifiex_11h_get_csa_closed_channel(struct mwifiex_private *priv)
{
	if (!priv->csa_chan)
		return 0;

	/* Clear csa channel, if DFS channel move time has passed */
	if (time_after(jiffies, priv->csa_expire_time)) {
		priv->csa_chan = 0;
		priv->csa_expire_time = 0;
	}

	return priv->csa_chan;
}