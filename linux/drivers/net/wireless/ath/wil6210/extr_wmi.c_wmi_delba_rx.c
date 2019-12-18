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
typedef  int /*<<< orphan*/  u16 ;
struct wmi_rcp_delba_cmd {int /*<<< orphan*/  cidxtid; scalar_t__ tid; scalar_t__ cid; int /*<<< orphan*/  reason; } ;
struct wil6210_priv {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CIDXTID_EXTENDED_CID_TID ; 
 scalar_t__ WIL6210_RX_DESC_MAX_CID ; 
 int /*<<< orphan*/  WMI_RCP_DELBA_CMDID ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_cidxtid (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wil_dbg_wmi (struct wil6210_priv*,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,scalar_t__,struct wmi_rcp_delba_cmd*,int) ; 

int wmi_delba_rx(struct wil6210_priv *wil, u8 mid, u8 cid, u8 tid, u16 reason)
{
	struct wmi_rcp_delba_cmd cmd = {
		.reason = cpu_to_le16(reason),
	};

	if (cid >= WIL6210_RX_DESC_MAX_CID) {
		cmd.cidxtid = CIDXTID_EXTENDED_CID_TID;
		cmd.cid = cid;
		cmd.tid = tid;
	} else {
		cmd.cidxtid = mk_cidxtid(cid, tid);
	}

	wil_dbg_wmi(wil, "delba_rx: (CID %d TID %d reason %d)\n", cid,
		    tid, reason);

	return wmi_send(wil, WMI_RCP_DELBA_CMDID, mid, &cmd, sizeof(cmd));
}