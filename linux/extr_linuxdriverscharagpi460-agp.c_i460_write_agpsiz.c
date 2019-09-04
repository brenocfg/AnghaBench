#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I460_AGPSIZ_MASK ; 
 int /*<<< orphan*/  INTEL_I460_AGPSIZ ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  pci_read_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i460_write_agpsiz (u8 size_value)
{
	u8 temp;

	pci_read_config_byte(agp_bridge->dev, INTEL_I460_AGPSIZ, &temp);
	pci_write_config_byte(agp_bridge->dev, INTEL_I460_AGPSIZ,
			      ((temp & ~I460_AGPSIZ_MASK) | size_value));
}