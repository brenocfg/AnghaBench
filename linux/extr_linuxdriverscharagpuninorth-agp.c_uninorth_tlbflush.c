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
typedef  int u32 ;
struct agp_memory {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int U3_N_CFG_GART_PERFRD ; 
 int UNI_N_CFG_GART_2xRESET ; 
 int /*<<< orphan*/  UNI_N_CFG_GART_CTRL ; 
 int UNI_N_CFG_GART_ENABLE ; 
 int UNI_N_CFG_GART_INVAL ; 
 TYPE_1__* agp_bridge ; 
 scalar_t__ is_u3 ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int uninorth_rev ; 

__attribute__((used)) static void uninorth_tlbflush(struct agp_memory *mem)
{
	u32 ctrl = UNI_N_CFG_GART_ENABLE;

	if (is_u3)
		ctrl |= U3_N_CFG_GART_PERFRD;
	pci_write_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL,
			       ctrl | UNI_N_CFG_GART_INVAL);
	pci_write_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL, ctrl);

	if (!mem && uninorth_rev <= 0x30) {
		pci_write_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL,
				       ctrl | UNI_N_CFG_GART_2xRESET);
		pci_write_config_dword(agp_bridge->dev, UNI_N_CFG_GART_CTRL,
				       ctrl);
	}
}