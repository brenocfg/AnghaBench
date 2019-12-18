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
struct brcmf_cfg80211_info {int dummy; } ;
struct brcmf_cfg80211_connect_info {scalar_t__ resp_ie_len; int /*<<< orphan*/ * resp_ie; scalar_t__ req_ie_len; int /*<<< orphan*/ * req_ie; } ;

/* Variables and functions */
 struct brcmf_cfg80211_connect_info* cfg_to_conn (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmf_clear_assoc_ies(struct brcmf_cfg80211_info *cfg)
{
	struct brcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);

	kfree(conn_info->req_ie);
	conn_info->req_ie = NULL;
	conn_info->req_ie_len = 0;
	kfree(conn_info->resp_ie);
	conn_info->resp_ie = NULL;
	conn_info->resp_ie_len = 0;
}