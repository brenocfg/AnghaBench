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
typedef  int /*<<< orphan*/  u16 ;
struct ssb_bus {int sdio_sbaddr; int /*<<< orphan*/  host_sdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_sdio_dev (struct ssb_bus*) ; 
 scalar_t__ unlikely (int) ; 

u32 ssb_sdio_scan_read32(struct ssb_bus *bus, u16 offset)
{
	u32 val;
	int error;

	sdio_claim_host(bus->host_sdio);
	val = sdio_readl(bus->host_sdio, offset, &error);
	sdio_release_host(bus->host_sdio);
	if (unlikely(error)) {
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X > %08x, error %d\n",
			bus->sdio_sbaddr >> 16, offset, val, error);
	}

	return val;
}