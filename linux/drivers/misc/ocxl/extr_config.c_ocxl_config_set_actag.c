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
typedef  int u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int OCXL_DVSEC_ACTAG_MASK ; 
 scalar_t__ OCXL_DVSEC_FUNC_OFF_ACTAG ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,scalar_t__,int) ; 

void ocxl_config_set_actag(struct pci_dev *dev, int func_dvsec, u32 tag_first,
			u32 tag_count)
{
	u32 val;

	val = (tag_first & OCXL_DVSEC_ACTAG_MASK) << 16;
	val |= tag_count & OCXL_DVSEC_ACTAG_MASK;
	pci_write_config_dword(dev, func_dvsec + OCXL_DVSEC_FUNC_OFF_ACTAG,
			val);
}