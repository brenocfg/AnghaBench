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
struct tcpci {int /*<<< orphan*/  regmap; } ;
struct tcpc_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCPC_CMD_DISABLE_SINK_VBUS ; 
 int /*<<< orphan*/  TCPC_CMD_DISABLE_SRC_VBUS ; 
 int /*<<< orphan*/  TCPC_CMD_SINK_VBUS ; 
 int /*<<< orphan*/  TCPC_CMD_SRC_VBUS_DEFAULT ; 
 int /*<<< orphan*/  TCPC_COMMAND ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcpci* tcpc_to_tcpci (struct tcpc_dev*) ; 

__attribute__((used)) static int tcpci_set_vbus(struct tcpc_dev *tcpc, bool source, bool sink)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	int ret;

	/* Disable both source and sink first before enabling anything */

	if (!source) {
		ret = regmap_write(tcpci->regmap, TCPC_COMMAND,
				   TCPC_CMD_DISABLE_SRC_VBUS);
		if (ret < 0)
			return ret;
	}

	if (!sink) {
		ret = regmap_write(tcpci->regmap, TCPC_COMMAND,
				   TCPC_CMD_DISABLE_SINK_VBUS);
		if (ret < 0)
			return ret;
	}

	if (source) {
		ret = regmap_write(tcpci->regmap, TCPC_COMMAND,
				   TCPC_CMD_SRC_VBUS_DEFAULT);
		if (ret < 0)
			return ret;
	}

	if (sink) {
		ret = regmap_write(tcpci->regmap, TCPC_COMMAND,
				   TCPC_CMD_SINK_VBUS);
		if (ret < 0)
			return ret;
	}

	return 0;
}