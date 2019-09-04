#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sh_mmcif_host {scalar_t__ sg_blkidx; scalar_t__ blocksize; scalar_t__ sg_idx; int /*<<< orphan*/ * pio_ptr; TYPE_1__* mrq; } ;
struct mmc_data {scalar_t__ sg_len; TYPE_2__* sg; } ;
struct TYPE_4__ {scalar_t__ length; } ;
struct TYPE_3__ {struct mmc_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/ * sg_virt (TYPE_2__*) ; 

__attribute__((used)) static bool sh_mmcif_next_block(struct sh_mmcif_host *host, u32 *p)
{
	struct mmc_data *data = host->mrq->data;

	host->sg_blkidx += host->blocksize;

	/* data->sg->length must be a multiple of host->blocksize? */
	BUG_ON(host->sg_blkidx > data->sg->length);

	if (host->sg_blkidx == data->sg->length) {
		host->sg_blkidx = 0;
		if (++host->sg_idx < data->sg_len)
			host->pio_ptr = sg_virt(++data->sg);
	} else {
		host->pio_ptr = p;
	}

	return host->sg_idx != data->sg_len;
}