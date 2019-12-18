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
struct NCR5380_hostdata {int pdma_residual; } ;

/* Variables and functions */

__attribute__((used)) static int generic_NCR5380_dma_residual(struct NCR5380_hostdata *hostdata)
{
	return hostdata->pdma_residual;
}