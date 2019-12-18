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
typedef  int u16 ;
typedef  enum hl_asic_type { ____Placeholder_hl_asic_type } hl_asic_type ;

/* Variables and functions */
 int ASIC_GOYA ; 
 int ASIC_INVALID ; 
#define  PCI_IDS_GOYA 128 

__attribute__((used)) static enum hl_asic_type get_asic_type(u16 device)
{
	enum hl_asic_type asic_type;

	switch (device) {
	case PCI_IDS_GOYA:
		asic_type = ASIC_GOYA;
		break;
	default:
		asic_type = ASIC_INVALID;
		break;
	}

	return asic_type;
}