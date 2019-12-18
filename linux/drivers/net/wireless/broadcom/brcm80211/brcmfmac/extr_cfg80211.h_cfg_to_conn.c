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
struct brcmf_cfg80211_connect_info {int dummy; } ;
struct brcmf_cfg80211_info {struct brcmf_cfg80211_connect_info conn_info; } ;

/* Variables and functions */

__attribute__((used)) static inline struct
brcmf_cfg80211_connect_info *cfg_to_conn(struct brcmf_cfg80211_info *cfg)
{
	return &cfg->conn_info;
}