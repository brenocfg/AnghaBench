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
typedef  int u16 ;
struct mwifiex_private {TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_cap_info; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  HostCmd_CMD_802_11_AD_HOC_JOIN 131 
#define  HostCmd_CMD_802_11_AD_HOC_START 130 
#define  HostCmd_CMD_802_11_AD_HOC_STOP 129 
#define  HostCmd_CMD_802_11_IBSS_COALESCING_STATUS 128 
 int /*<<< orphan*/  ISSUPP_ADHOC_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_is_cmd_supported(struct mwifiex_private *priv, u16 cmd_no)
{
	if (!ISSUPP_ADHOC_ENABLED(priv->adapter->fw_cap_info)) {
		switch (cmd_no) {
		case HostCmd_CMD_802_11_IBSS_COALESCING_STATUS:
		case HostCmd_CMD_802_11_AD_HOC_START:
		case HostCmd_CMD_802_11_AD_HOC_JOIN:
		case HostCmd_CMD_802_11_AD_HOC_STOP:
			return -EOPNOTSUPP;
		default:
			break;
		}
	}

	return 0;
}