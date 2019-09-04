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
typedef  int /*<<< orphan*/  u32 ;
struct tmio_mmc_host {int bus_shift; } ;
struct renesas_sdhi {scalar_t__ scc_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u32 sd_scc_read32(struct tmio_mmc_host *host,
				struct renesas_sdhi *priv, int addr)
{
	return readl(priv->scc_ctl + (addr << host->bus_shift));
}