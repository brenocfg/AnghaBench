#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int start; scalar_t__ size; } ;
struct TYPE_4__ {TYPE_1__ ocq; } ;
struct adapter {TYPE_2__ vres; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int BIR_V (int) ; 
 scalar_t__ OCQ_WIN_OFFSET (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_BASE_WIN_A ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_OFFSET_A ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_2 ; 
 int PCI_BASE_ADDRESS_MEM_MASK ; 
 int WINDOW_V (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (unsigned int) ; 
 int roundup_pow_of_two (scalar_t__) ; 
 int t4_read_pcie_cfg4 (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void setup_memwin_rdma(struct adapter *adap)
{
	if (adap->vres.ocq.size) {
		u32 start;
		unsigned int sz_kb;

		start = t4_read_pcie_cfg4(adap, PCI_BASE_ADDRESS_2);
		start &= PCI_BASE_ADDRESS_MEM_MASK;
		start += OCQ_WIN_OFFSET(adap->pdev, &adap->vres);
		sz_kb = roundup_pow_of_two(adap->vres.ocq.size) >> 10;
		t4_write_reg(adap,
			     PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN_A, 3),
			     start | BIR_V(1) | WINDOW_V(ilog2(sz_kb)));
		t4_write_reg(adap,
			     PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET_A, 3),
			     adap->vres.ocq.start);
		t4_read_reg(adap,
			    PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET_A, 3));
	}
}