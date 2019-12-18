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
typedef  size_t u8 ;
struct ath6kl_sta {size_t aid; } ;
struct ath6kl {struct ath6kl_sta* sta_list; } ;

/* Variables and functions */
 size_t AP_MAX_NUM_STA ; 

struct ath6kl_sta *ath6kl_find_sta_by_aid(struct ath6kl *ar, u8 aid)
{
	struct ath6kl_sta *conn = NULL;
	u8 ctr;

	for (ctr = 0; ctr < AP_MAX_NUM_STA; ctr++) {
		if (ar->sta_list[ctr].aid == aid) {
			conn = &ar->sta_list[ctr];
			break;
		}
	}
	return conn;
}