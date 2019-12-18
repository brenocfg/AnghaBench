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
struct NCR_700_Host_Parameters {int base; } ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ bEBus ; 
 int /*<<< orphan*/  iowrite32 (int,int) ; 
 int /*<<< orphan*/  iowrite32be (int,int) ; 

__attribute__((used)) static inline void
NCR_700_writel(__u32 value, struct Scsi_Host *host, __u32 reg)
{
	const struct NCR_700_Host_Parameters *hostdata
		= (struct NCR_700_Host_Parameters *)host->hostdata[0];

#if 1
	/* sanity check the register */
	BUG_ON((reg & 0x3) != 0);
#endif

	bEBus ? iowrite32be(value, hostdata->base + reg): 
		iowrite32(value, hostdata->base + reg);
}