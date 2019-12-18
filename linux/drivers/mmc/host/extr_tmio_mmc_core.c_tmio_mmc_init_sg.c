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
struct tmio_mmc_host {scalar_t__ sg_off; int /*<<< orphan*/  sg_orig; int /*<<< orphan*/  sg_ptr; int /*<<< orphan*/  sg_len; } ;
struct mmc_data {int /*<<< orphan*/  sg; int /*<<< orphan*/  sg_len; } ;

/* Variables and functions */

__attribute__((used)) static void tmio_mmc_init_sg(struct tmio_mmc_host *host, struct mmc_data *data)
{
	host->sg_len = data->sg_len;
	host->sg_ptr = data->sg;
	host->sg_orig = data->sg;
	host->sg_off = 0;
}