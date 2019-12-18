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
typedef  void* u32 ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int dummy; } ;
struct brcmf_cfg80211_info {scalar_t__ extra_buf; struct brcmf_pub* pub; } ;
struct brcmf_cfg80211_connect_info {void* resp_ie_len; void* req_ie_len; int /*<<< orphan*/ * resp_ie; int /*<<< orphan*/ * req_ie; } ;
struct brcmf_cfg80211_assoc_ielen_le {int /*<<< orphan*/  resp_len; int /*<<< orphan*/  req_len; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CONN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WL_ASSOC_INFO_MAX ; 
 int /*<<< orphan*/  bphy_err (struct brcmf_pub*,char*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_clear_assoc_ies (struct brcmf_cfg80211_info*) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,void*,void*) ; 
 scalar_t__ brcmf_fil_iovar_data_get (struct brcmf_if*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct brcmf_cfg80211_connect_info* cfg_to_conn (struct brcmf_cfg80211_info*) ; 
 void* kmemdup (scalar_t__,void*,int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 brcmf_get_assoc_ies(struct brcmf_cfg80211_info *cfg,
			       struct brcmf_if *ifp)
{
	struct brcmf_pub *drvr = cfg->pub;
	struct brcmf_cfg80211_assoc_ielen_le *assoc_info;
	struct brcmf_cfg80211_connect_info *conn_info = cfg_to_conn(cfg);
	u32 req_len;
	u32 resp_len;
	s32 err = 0;

	brcmf_clear_assoc_ies(cfg);

	err = brcmf_fil_iovar_data_get(ifp, "assoc_info",
				       cfg->extra_buf, WL_ASSOC_INFO_MAX);
	if (err) {
		bphy_err(drvr, "could not get assoc info (%d)\n", err);
		return err;
	}
	assoc_info =
		(struct brcmf_cfg80211_assoc_ielen_le *)cfg->extra_buf;
	req_len = le32_to_cpu(assoc_info->req_len);
	resp_len = le32_to_cpu(assoc_info->resp_len);
	if (req_len) {
		err = brcmf_fil_iovar_data_get(ifp, "assoc_req_ies",
					       cfg->extra_buf,
					       WL_ASSOC_INFO_MAX);
		if (err) {
			bphy_err(drvr, "could not get assoc req (%d)\n", err);
			return err;
		}
		conn_info->req_ie_len = req_len;
		conn_info->req_ie =
		    kmemdup(cfg->extra_buf, conn_info->req_ie_len,
			    GFP_KERNEL);
		if (!conn_info->req_ie)
			conn_info->req_ie_len = 0;
	} else {
		conn_info->req_ie_len = 0;
		conn_info->req_ie = NULL;
	}
	if (resp_len) {
		err = brcmf_fil_iovar_data_get(ifp, "assoc_resp_ies",
					       cfg->extra_buf,
					       WL_ASSOC_INFO_MAX);
		if (err) {
			bphy_err(drvr, "could not get assoc resp (%d)\n", err);
			return err;
		}
		conn_info->resp_ie_len = resp_len;
		conn_info->resp_ie =
		    kmemdup(cfg->extra_buf, conn_info->resp_ie_len,
			    GFP_KERNEL);
		if (!conn_info->resp_ie)
			conn_info->resp_ie_len = 0;
	} else {
		conn_info->resp_ie_len = 0;
		conn_info->resp_ie = NULL;
	}
	brcmf_dbg(CONN, "req len (%d) resp len (%d)\n",
		  conn_info->req_ie_len, conn_info->resp_ie_len);

	return err;
}