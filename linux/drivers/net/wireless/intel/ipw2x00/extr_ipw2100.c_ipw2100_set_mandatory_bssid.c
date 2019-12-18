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
struct ipw2100_priv {int dummy; } ;
struct host_command {int /*<<< orphan*/  host_command_parameters; int /*<<< orphan*/  host_command_length; int /*<<< orphan*/  host_command_sequence; int /*<<< orphan*/  host_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*,...) ; 
 int /*<<< orphan*/  MANDATORY_BSSID ; 
 int ipw2100_disable_adapter (struct ipw2100_priv*) ; 
 int /*<<< orphan*/  ipw2100_enable_adapter (struct ipw2100_priv*) ; 
 int ipw2100_hw_send_command (struct ipw2100_priv*,struct host_command*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw2100_set_mandatory_bssid(struct ipw2100_priv *priv, u8 * bssid,
				       int batch_mode)
{
	struct host_command cmd = {
		.host_command = MANDATORY_BSSID,
		.host_command_sequence = 0,
		.host_command_length = (bssid == NULL) ? 0 : ETH_ALEN
	};
	int err;

#ifdef CONFIG_IPW2100_DEBUG
	if (bssid != NULL)
		IPW_DEBUG_HC("MANDATORY_BSSID: %pM\n", bssid);
	else
		IPW_DEBUG_HC("MANDATORY_BSSID: <clear>\n");
#endif
	/* if BSSID is empty then we disable mandatory bssid mode */
	if (bssid != NULL)
		memcpy(cmd.host_command_parameters, bssid, ETH_ALEN);

	if (!batch_mode) {
		err = ipw2100_disable_adapter(priv);
		if (err)
			return err;
	}

	err = ipw2100_hw_send_command(priv, &cmd);

	if (!batch_mode)
		ipw2100_enable_adapter(priv);

	return err;
}