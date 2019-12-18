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
typedef  int u8 ;
struct mwifiex_private {int* bitmap_rates; scalar_t__ is_data_rate_auto; TYPE_1__* aggr_prio_tbl; } ;
struct TYPE_2__ {scalar_t__ amsdu; } ;

/* Variables and functions */
 scalar_t__ BA_STREAM_NOT_ALLOWED ; 

__attribute__((used)) static inline u8
mwifiex_is_amsdu_allowed(struct mwifiex_private *priv, int tid)
{
	return (((priv->aggr_prio_tbl[tid].amsdu != BA_STREAM_NOT_ALLOWED) &&
		 (priv->is_data_rate_auto || !(priv->bitmap_rates[2] & 0x03)))
		? true : false);
}