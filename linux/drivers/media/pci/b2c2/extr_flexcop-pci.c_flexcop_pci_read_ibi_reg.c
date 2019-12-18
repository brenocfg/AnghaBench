#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct flexcop_pci {scalar_t__ io_mem; } ;
struct flexcop_device {struct flexcop_pci* bus_specific; } ;
struct TYPE_3__ {scalar_t__ raw; } ;
typedef  TYPE_1__ flexcop_ibi_value ;
typedef  scalar_t__ flexcop_ibi_register ;

/* Variables and functions */
 int /*<<< orphan*/  deb_reg (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ lastrreg ; 
 scalar_t__ lastrval ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static flexcop_ibi_value flexcop_pci_read_ibi_reg(struct flexcop_device *fc,
		flexcop_ibi_register r)
{
	struct flexcop_pci *fc_pci = fc->bus_specific;
	flexcop_ibi_value v;
	v.raw = readl(fc_pci->io_mem + r);

	if (lastrreg != r || lastrval != v.raw) {
		lastrreg = r; lastrval = v.raw;
		deb_reg("new rd: %3x: %08x\n", r, v.raw);
	}

	return v;
}