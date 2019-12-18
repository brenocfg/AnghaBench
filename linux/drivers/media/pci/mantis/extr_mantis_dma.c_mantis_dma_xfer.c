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
struct mantis_pci {size_t last_block; size_t busy_block; int /*<<< orphan*/ * buf_cpu; int /*<<< orphan*/  demux; struct mantis_hwconfig* hwconfig; } ;
struct mantis_hwconfig {scalar_t__ ts_size; } ;

/* Variables and functions */
 size_t MANTIS_BLOCK_BYTES ; 
 int MANTIS_BLOCK_COUNT ; 
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,size_t,size_t) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dvb_dmx_swfilter_204 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

void mantis_dma_xfer(unsigned long data)
{
	struct mantis_pci *mantis = (struct mantis_pci *) data;
	struct mantis_hwconfig *config = mantis->hwconfig;

	while (mantis->last_block != mantis->busy_block) {
		dprintk(MANTIS_DEBUG, 1, "last block=[%d] finished block=[%d]",
			mantis->last_block, mantis->busy_block);

		(config->ts_size ? dvb_dmx_swfilter_204 : dvb_dmx_swfilter)
		(&mantis->demux, &mantis->buf_cpu[mantis->last_block * MANTIS_BLOCK_BYTES], MANTIS_BLOCK_BYTES);
		mantis->last_block = (mantis->last_block + 1) % MANTIS_BLOCK_COUNT;
	}
}