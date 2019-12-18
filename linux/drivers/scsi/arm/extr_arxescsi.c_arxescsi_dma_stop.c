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
struct scsi_pointer {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void arxescsi_dma_stop(struct Scsi_Host *host, struct scsi_pointer *SCp)
{
	/*
	 * no DMA to stop
	 */
}