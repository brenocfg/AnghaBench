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
typedef  int u8 ;
typedef  int u16 ;
struct ssb_device {struct ssb_bus* bus; } ;
struct ssb_bus {int sdio_sbaddr; int /*<<< orphan*/  host_sdio; } ;

/* Variables and functions */
 int SBSDIO_SB_OFT_ADDR_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int sdio_readb (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssb_sdio_dev (struct ssb_bus*) ; 
 int /*<<< orphan*/  ssb_sdio_switch_core (struct ssb_bus*,struct ssb_device*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 ssb_sdio_read8(struct ssb_device *dev, u16 offset)
{
	struct ssb_bus *bus = dev->bus;
	u8 val = 0xff;
	int error = 0;

	sdio_claim_host(bus->host_sdio);
	if (unlikely(ssb_sdio_switch_core(bus, dev)))
		goto out;
	offset |= bus->sdio_sbaddr & 0xffff;
	offset &= SBSDIO_SB_OFT_ADDR_MASK;
	val = sdio_readb(bus->host_sdio, offset, &error);
	if (error) {
		dev_dbg(ssb_sdio_dev(bus), "%04X:%04X > %02x, error %d\n",
			bus->sdio_sbaddr >> 16, offset, val, error);
	}
out:
	sdio_release_host(bus->host_sdio);

	return val;
}