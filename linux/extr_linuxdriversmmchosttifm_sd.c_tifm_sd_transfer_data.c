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
struct tifm_sd {size_t sg_pos; size_t sg_len; unsigned int block_pos; int cmd_flags; TYPE_3__* dev; int /*<<< orphan*/ * bounce_buf_data; TYPE_2__* req; } ;
struct scatterlist {unsigned int length; unsigned int offset; } ;
struct page {int dummy; } ;
struct mmc_data {int flags; struct scatterlist* sg; } ;
struct TYPE_6__ {scalar_t__ addr; } ;
struct TYPE_5__ {TYPE_1__* cmd; } ;
struct TYPE_4__ {struct mmc_data* data; } ;

/* Variables and functions */
 int DATA_CARRY ; 
 int MMC_DATA_READ ; 
 int MMC_DATA_WRITE ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ SOCK_MMCSD_DATA ; 
 int TIFM_MMCSD_FIFO_SIZE ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct page* nth_page (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int offset_in_page (unsigned int) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  tifm_sd_read_fifo (struct tifm_sd*,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  tifm_sd_write_fifo (struct tifm_sd*,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tifm_sd_transfer_data(struct tifm_sd *host)
{
	struct mmc_data *r_data = host->req->cmd->data;
	struct scatterlist *sg = r_data->sg;
	unsigned int off, cnt, t_size = TIFM_MMCSD_FIFO_SIZE * 2;
	unsigned int p_off, p_cnt;
	struct page *pg;

	if (host->sg_pos == host->sg_len)
		return;
	while (t_size) {
		cnt = sg[host->sg_pos].length - host->block_pos;
		if (!cnt) {
			host->block_pos = 0;
			host->sg_pos++;
			if (host->sg_pos == host->sg_len) {
				if ((r_data->flags & MMC_DATA_WRITE)
				    && (host->cmd_flags & DATA_CARRY))
					writel(host->bounce_buf_data[0],
					       host->dev->addr
					       + SOCK_MMCSD_DATA);

				return;
			}
			cnt = sg[host->sg_pos].length;
		}
		off = sg[host->sg_pos].offset + host->block_pos;

		pg = nth_page(sg_page(&sg[host->sg_pos]), off >> PAGE_SHIFT);
		p_off = offset_in_page(off);
		p_cnt = PAGE_SIZE - p_off;
		p_cnt = min(p_cnt, cnt);
		p_cnt = min(p_cnt, t_size);

		if (r_data->flags & MMC_DATA_READ)
			tifm_sd_read_fifo(host, pg, p_off, p_cnt);
		else if (r_data->flags & MMC_DATA_WRITE)
			tifm_sd_write_fifo(host, pg, p_off, p_cnt);

		t_size -= p_cnt;
		host->block_pos += p_cnt;
	}
}