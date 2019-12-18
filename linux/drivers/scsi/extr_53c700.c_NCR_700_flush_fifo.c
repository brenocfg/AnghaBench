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
struct Scsi_Host {scalar_t__* hostdata; } ;
struct NCR_700_Host_Parameters {scalar_t__ chip710; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTEST8_REG ; 
 int /*<<< orphan*/  DFIFO_REG ; 
 int /*<<< orphan*/  FLUSH_DMA_FIFO ; 
 int /*<<< orphan*/  FLUSH_DMA_FIFO_710 ; 
 int /*<<< orphan*/  NCR_700_writeb (int /*<<< orphan*/ ,struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void
NCR_700_flush_fifo(struct Scsi_Host *host) {
	const struct NCR_700_Host_Parameters *hostdata
		= (struct NCR_700_Host_Parameters *)host->hostdata[0];
	if(hostdata->chip710) {
		NCR_700_writeb(FLUSH_DMA_FIFO_710, host, CTEST8_REG);
		udelay(10);
		NCR_700_writeb(0, host, CTEST8_REG);
	} else {
		NCR_700_writeb(FLUSH_DMA_FIFO, host, DFIFO_REG);
		udelay(10);
		NCR_700_writeb(0, host, DFIFO_REG);
	}
}