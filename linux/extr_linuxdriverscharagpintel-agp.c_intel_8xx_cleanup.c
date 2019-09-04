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
typedef  int u16 ;
struct aper_size_info_8 {int /*<<< orphan*/  size_value; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  previous_size; } ;

/* Variables and functions */
 struct aper_size_info_8* A_SIZE_8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_APSIZE ; 
 int /*<<< orphan*/  INTEL_NBXCFG ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void intel_8xx_cleanup(void)
{
	u16 temp;
	struct aper_size_info_8 *previous_size;

	previous_size = A_SIZE_8(agp_bridge->previous_size);
	pci_read_config_word(agp_bridge->dev, INTEL_NBXCFG, &temp);
	pci_write_config_word(agp_bridge->dev, INTEL_NBXCFG, temp & ~(1 << 9));
	pci_write_config_byte(agp_bridge->dev, INTEL_APSIZE, previous_size->size_value);
}