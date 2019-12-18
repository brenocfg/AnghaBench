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

/* Variables and functions */
 int QUP_IO_M_MODE_BAM ; 
 int QUP_IO_M_MODE_DMOV ; 

__attribute__((used)) static inline bool spi_qup_is_dma_xfer(int mode)
{
	if (mode == QUP_IO_M_MODE_DMOV || mode == QUP_IO_M_MODE_BAM)
		return true;

	return false;
}