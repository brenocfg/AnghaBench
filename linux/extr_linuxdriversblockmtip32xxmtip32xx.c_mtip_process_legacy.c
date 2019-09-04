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
typedef  int /*<<< orphan*/  u32 ;
struct mtip_port {int /*<<< orphan*/ * cmd_issue; int /*<<< orphan*/  flags; } ;
struct mtip_cmd {int dummy; } ;
struct driver_data {struct mtip_port* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTIP_PF_IC_ACTIVE_BIT ; 
 int MTIP_TAG_BIT (int /*<<< orphan*/ ) ; 
 int MTIP_TAG_INDEX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTIP_TAG_INTERNAL ; 
 struct mtip_cmd* mtip_cmd_from_tag (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtip_complete_command (struct mtip_cmd*,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mtip_process_legacy(struct driver_data *dd, u32 port_stat)
{
	struct mtip_port *port = dd->port;
	struct mtip_cmd *cmd = mtip_cmd_from_tag(dd, MTIP_TAG_INTERNAL);

	if (test_bit(MTIP_PF_IC_ACTIVE_BIT, &port->flags) && cmd) {
		int group = MTIP_TAG_INDEX(MTIP_TAG_INTERNAL);
		int status = readl(port->cmd_issue[group]);

		if (!(status & (1 << MTIP_TAG_BIT(MTIP_TAG_INTERNAL))))
			mtip_complete_command(cmd, 0);
	}
}