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
struct mmc_command {int flags; scalar_t__ data; } ;

/* Variables and functions */
 int MMC_RSP_BUSY ; 

__attribute__((used)) static inline bool sdhci_data_line_cmd(struct mmc_command *cmd)
{
	return cmd->data || cmd->flags & MMC_RSP_BUSY;
}