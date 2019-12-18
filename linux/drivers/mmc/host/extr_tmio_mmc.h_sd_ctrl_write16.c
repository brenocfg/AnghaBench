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
typedef  int /*<<< orphan*/  u16 ;
struct tmio_mmc_host {int bus_shift; scalar_t__ ctl; scalar_t__ (* write16_hook ) (struct tmio_mmc_host*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ stub1 (struct tmio_mmc_host*,int) ; 

__attribute__((used)) static inline void sd_ctrl_write16(struct tmio_mmc_host *host, int addr,
				   u16 val)
{
	/* If there is a hook and it returns non-zero then there
	 * is an error and the write should be skipped
	 */
	if (host->write16_hook && host->write16_hook(host, addr))
		return;
	iowrite16(val, host->ctl + (addr << host->bus_shift));
}