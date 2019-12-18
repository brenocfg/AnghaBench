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
typedef  int u8 ;
struct mwifiex_sta_node {scalar_t__* ampdu_sta; } ;
struct mwifiex_ra_list_tbl {int /*<<< orphan*/  ra; } ;
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ BA_STREAM_NOT_ALLOWED ; 
 struct mwifiex_sta_node* mwifiex_get_sta_entry (struct mwifiex_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline u8
mwifiex_is_station_ampdu_allowed(struct mwifiex_private *priv,
				 struct mwifiex_ra_list_tbl *ptr, int tid)
{
	struct mwifiex_sta_node *node = mwifiex_get_sta_entry(priv, ptr->ra);

	if (unlikely(!node))
		return false;

	return (node->ampdu_sta[tid] != BA_STREAM_NOT_ALLOWED) ? true : false;
}