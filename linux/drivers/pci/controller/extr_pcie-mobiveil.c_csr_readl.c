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
typedef  int /*<<< orphan*/  u32 ;
struct mobiveil_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  csr_read (struct mobiveil_pcie*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 csr_readl(struct mobiveil_pcie *pcie, u32 off)
{
	return csr_read(pcie, off, 0x4);
}