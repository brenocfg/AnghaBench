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
struct mmc_data {int dummy; } ;
struct mmc_command {int dummy; } ;
struct dw_mci {int /*<<< orphan*/  stop_cmdr; struct mmc_command stop_abort; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_mci_start_command (struct dw_mci*,struct mmc_command*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void send_stop_abort(struct dw_mci *host, struct mmc_data *data)
{
	struct mmc_command *stop = &host->stop_abort;

	dw_mci_start_command(host, stop, host->stop_cmdr);
}