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
typedef  int u32 ;
struct tmio_mmc_host {int bus_shift; scalar_t__ ctl; } ;

/* Variables and functions */
 int ioread16 (scalar_t__) ; 

__attribute__((used)) static inline u32 sd_ctrl_read16_and_16_as_32(struct tmio_mmc_host *host,
					      int addr)
{
	return ioread16(host->ctl + (addr << host->bus_shift)) |
	       ioread16(host->ctl + ((addr + 2) << host->bus_shift)) << 16;
}