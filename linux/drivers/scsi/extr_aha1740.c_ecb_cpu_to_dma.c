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
struct aha1740_hostdata {int ecb_dma_addr; scalar_t__ ecb; } ;
struct Scsi_Host {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 struct aha1740_hostdata* HOSTDATA (struct Scsi_Host*) ; 

__attribute__((used)) static inline dma_addr_t ecb_cpu_to_dma (struct Scsi_Host *host, void *cpu)
{
	struct aha1740_hostdata *hdata = HOSTDATA (host);
	dma_addr_t offset;
    
	offset = (char *) cpu - (char *) hdata->ecb;

	return hdata->ecb_dma_addr + offset;
}