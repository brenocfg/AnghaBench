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
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASIC_PCIE_SD_INTRPT_LIST ; 
 int ASIC_PCIE_SD_INTRPT_LIST_INTRPT_CODE_SHIFT ; 
 int ASIC_PCIE_SD_INTRPT_LIST_INTRPT_DATA_SHIFT ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int) ; 

__attribute__((used)) static void write_gasket_interrupt(struct hfi1_devdata *dd, int index,
				   u16 code, u16 data)
{
	write_csr(dd, ASIC_PCIE_SD_INTRPT_LIST + (index * 8),
		  (((u64)code << ASIC_PCIE_SD_INTRPT_LIST_INTRPT_CODE_SHIFT) |
		   ((u64)data << ASIC_PCIE_SD_INTRPT_LIST_INTRPT_DATA_SHIFT)));
}