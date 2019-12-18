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
struct wil6210_priv {int max_assoc_sta; TYPE_1__* sta; } ;
struct TYPE_2__ {scalar_t__ status; scalar_t__ mid; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ wil_sta_unused ; 

int wil_find_cid_by_idx(struct wil6210_priv *wil, u8 mid, int idx)
{
	int i;

	for (i = 0; i < wil->max_assoc_sta; i++) {
		if (wil->sta[i].status == wil_sta_unused)
			continue;
		if (wil->sta[i].mid != mid)
			continue;
		if (idx == 0)
			return i;
		idx--;
	}

	return -ENOENT;
}