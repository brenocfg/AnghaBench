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
struct wbsd_host {TYPE_1__* cur_sg; int /*<<< orphan*/  remain; scalar_t__ offset; int /*<<< orphan*/  num_sg; } ;
struct mmc_data {int /*<<< orphan*/  sg_len; TYPE_1__* sg; } ;
struct TYPE_2__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */

__attribute__((used)) static inline void wbsd_init_sg(struct wbsd_host *host, struct mmc_data *data)
{
	/*
	 * Get info. about SG list from data structure.
	 */
	host->cur_sg = data->sg;
	host->num_sg = data->sg_len;

	host->offset = 0;
	host->remain = host->cur_sg->length;
}