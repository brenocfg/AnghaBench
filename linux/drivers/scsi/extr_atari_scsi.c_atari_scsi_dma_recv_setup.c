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
struct NCR5380_hostdata {int dummy; } ;

/* Variables and functions */
 int atari_scsi_dma_setup (struct NCR5380_hostdata*,unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int atari_scsi_dma_recv_setup(struct NCR5380_hostdata *hostdata,
                                            unsigned char *data, int count)
{
	return atari_scsi_dma_setup(hostdata, data, count, 0);
}