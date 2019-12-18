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
struct moxart_host {scalar_t__ data_remain; scalar_t__ data_len; TYPE_1__* cur_sg; int /*<<< orphan*/  num_sg; } ;
struct mmc_data {int /*<<< orphan*/  sg_len; TYPE_1__* sg; } ;
struct TYPE_2__ {scalar_t__ length; } ;

/* Variables and functions */

__attribute__((used)) static inline void moxart_init_sg(struct moxart_host *host,
				  struct mmc_data *data)
{
	host->cur_sg = data->sg;
	host->num_sg = data->sg_len;
	host->data_remain = host->cur_sg->length;

	if (host->data_remain > host->data_len)
		host->data_remain = host->data_len;
}