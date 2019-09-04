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
typedef  scalar_t__ u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LOG_SIZE ; 
 int /*<<< orphan*/  SZ_4K ; 
 scalar_t__ dma_zalloc_coherent (struct device*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioremap_nocache (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_lock ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ sdhost_log_addr ; 
 scalar_t__ sdhost_log_buf ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_base ; 

__attribute__((used)) static void log_init(struct device *dev, u32 bus_to_phys)
{
	spin_lock_init(&log_lock);
	sdhost_log_buf = dma_zalloc_coherent(dev, LOG_SIZE, &sdhost_log_addr,
					     GFP_KERNEL);
	if (sdhost_log_buf) {
		pr_info("sdhost: log_buf @ %p (%x)\n",
			sdhost_log_buf, (u32)sdhost_log_addr);
		timer_base = ioremap_nocache(bus_to_phys + 0x7e003000, SZ_4K);
		if (!timer_base)
			pr_err("sdhost: failed to remap timer\n");
	}
	else
		pr_err("sdhost: failed to allocate log buf\n");
}