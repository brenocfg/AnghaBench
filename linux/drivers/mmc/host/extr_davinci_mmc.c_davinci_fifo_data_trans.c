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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mmc_davinci_host {unsigned int buffer_bytes_left; unsigned int bytes_left; scalar_t__ data_dir; int /*<<< orphan*/ * buffer; scalar_t__ base; TYPE_1__* data; int /*<<< orphan*/  sg; } ;
struct TYPE_2__ {int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MMCDRR ; 
 scalar_t__ DAVINCI_MMCDXR ; 
 scalar_t__ DAVINCI_MMC_DATADIR_WRITE ; 
 int /*<<< orphan*/  ioread8_rep (scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  iowrite8_rep (scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mmc_davinci_sg_to_buf (struct mmc_davinci_host*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void davinci_fifo_data_trans(struct mmc_davinci_host *host,
					unsigned int n)
{
	u8 *p;
	unsigned int i;

	if (host->buffer_bytes_left == 0) {
		host->sg = sg_next(host->data->sg);
		mmc_davinci_sg_to_buf(host);
	}

	p = host->buffer;
	if (n > host->buffer_bytes_left)
		n = host->buffer_bytes_left;
	host->buffer_bytes_left -= n;
	host->bytes_left -= n;

	/* NOTE:  we never transfer more than rw_threshold bytes
	 * to/from the fifo here; there's no I/O overlap.
	 * This also assumes that access width( i.e. ACCWD) is 4 bytes
	 */
	if (host->data_dir == DAVINCI_MMC_DATADIR_WRITE) {
		for (i = 0; i < (n >> 2); i++) {
			writel(*((u32 *)p), host->base + DAVINCI_MMCDXR);
			p = p + 4;
		}
		if (n & 3) {
			iowrite8_rep(host->base + DAVINCI_MMCDXR, p, (n & 3));
			p = p + (n & 3);
		}
	} else {
		for (i = 0; i < (n >> 2); i++) {
			*((u32 *)p) = readl(host->base + DAVINCI_MMCDRR);
			p  = p + 4;
		}
		if (n & 3) {
			ioread8_rep(host->base + DAVINCI_MMCDRR, p, (n & 3));
			p = p + (n & 3);
		}
	}
	host->buffer = p;
}