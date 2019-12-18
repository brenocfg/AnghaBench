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
typedef  int /*<<< orphan*/  u64 ;
struct tmio_mmc_host {scalar_t__ ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
renesas_sdhi_internal_dmac_dm_write(struct tmio_mmc_host *host,
				    int addr, u64 val)
{
	writeq(val, host->ctl + addr);
}