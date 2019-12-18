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
struct NCR_700_Host_Parameters {scalar_t__ fast; scalar_t__ chip710; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  CTEST0_REG ; 
 int /*<<< orphan*/  DBC_REG ; 
 int /*<<< orphan*/  DFIFO_REG ; 
 int NCR_700_readb (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int NCR_700_readl (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 int SIDL_REG_FULL ; 
 int SODL_REG_FULL ; 
 int SODR_REG_FULL ; 
 int /*<<< orphan*/  SSTAT1_REG ; 
 int /*<<< orphan*/  SSTAT2_REG ; 
 int /*<<< orphan*/  SXFER_REG ; 
 int /*<<< orphan*/  printk (char*,int,unsigned int) ; 

__attribute__((used)) static inline int
NCR_700_data_residual (struct Scsi_Host *host) {
	struct NCR_700_Host_Parameters *hostdata = 
		(struct NCR_700_Host_Parameters *)host->hostdata[0];
	int count, synchronous = 0;
	unsigned int ddir;

	if(hostdata->chip710) {
		count = ((NCR_700_readb(host, DFIFO_REG) & 0x7f) -
			 (NCR_700_readl(host, DBC_REG) & 0x7f)) & 0x7f;
	} else {
		count = ((NCR_700_readb(host, DFIFO_REG) & 0x3f) -
			 (NCR_700_readl(host, DBC_REG) & 0x3f)) & 0x3f;
	}
	
	if(hostdata->fast)
		synchronous = NCR_700_readb(host, SXFER_REG) & 0x0f;
	
	/* get the data direction */
	ddir = NCR_700_readb(host, CTEST0_REG) & 0x01;

	if (ddir) {
		/* Receive */
		if (synchronous) 
			count += (NCR_700_readb(host, SSTAT2_REG) & 0xf0) >> 4;
		else
			if (NCR_700_readb(host, SSTAT1_REG) & SIDL_REG_FULL)
				++count;
	} else {
		/* Send */
		__u8 sstat = NCR_700_readb(host, SSTAT1_REG);
		if (sstat & SODL_REG_FULL)
			++count;
		if (synchronous && (sstat & SODR_REG_FULL))
			++count;
	}
#ifdef NCR_700_DEBUG
	if(count)
		printk("RESIDUAL IS %d (ddir %d)\n", count, ddir);
#endif
	return count;
}