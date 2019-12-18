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
typedef  int /*<<< orphan*/  u8 ;
struct ath_common {int dummy; } ;
struct ath9k_htc_target_rate {int dummy; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_CMD_BUF (int /*<<< orphan*/ ,struct ath9k_htc_target_rate*) ; 
 int /*<<< orphan*/  WMI_RC_RATE_UPDATE_CMDID ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*) ; 

__attribute__((used)) static int ath9k_htc_send_rate_cmd(struct ath9k_htc_priv *priv,
				    struct ath9k_htc_target_rate *trate)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	int ret;
	u8 cmd_rsp;

	WMI_CMD_BUF(WMI_RC_RATE_UPDATE_CMDID, trate);
	if (ret) {
		ath_err(common,
			"Unable to initialize Rate information on target\n");
	}

	return ret;
}