#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct moxart_host {scalar_t__ num_sg; int data_remain; int data_len; TYPE_3__* cur_sg; TYPE_2__* mrq; } ;
struct mmc_data {int bytes_xfered; } ;
struct TYPE_6__ {int length; } ;
struct TYPE_5__ {TYPE_1__* cmd; } ;
struct TYPE_4__ {struct mmc_data* data; } ;

/* Variables and functions */

__attribute__((used)) static inline int moxart_next_sg(struct moxart_host *host)
{
	int remain;
	struct mmc_data *data = host->mrq->cmd->data;

	host->cur_sg++;
	host->num_sg--;

	if (host->num_sg > 0) {
		host->data_remain = host->cur_sg->length;
		remain = host->data_len - data->bytes_xfered;
		if (remain > 0 && remain < host->data_remain)
			host->data_remain = remain;
	}

	return host->num_sg;
}