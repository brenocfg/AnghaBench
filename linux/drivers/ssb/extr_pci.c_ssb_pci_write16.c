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
typedef  scalar_t__ u16 ;
struct ssb_device {struct ssb_bus* bus; } ;
struct ssb_bus {scalar_t__ mmio; struct ssb_device* mapped_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite16 (scalar_t__,scalar_t__) ; 
 int ssb_pci_assert_buspower (struct ssb_bus*) ; 
 int ssb_pci_switch_core (struct ssb_bus*,struct ssb_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ssb_pci_write16(struct ssb_device *dev, u16 offset, u16 value)
{
	struct ssb_bus *bus = dev->bus;

	if (unlikely(ssb_pci_assert_buspower(bus)))
		return;
	if (unlikely(bus->mapped_device != dev)) {
		if (unlikely(ssb_pci_switch_core(bus, dev)))
			return;
	}
	iowrite16(value, bus->mmio + offset);
}