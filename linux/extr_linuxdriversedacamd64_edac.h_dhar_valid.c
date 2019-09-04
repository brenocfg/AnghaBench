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
typedef  int u8 ;
typedef  int u32 ;
struct amd64_pvt {int fam; int model; int dhar; int /*<<< orphan*/  F1; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRAM_CONT_BASE ; 
 int /*<<< orphan*/  amd64_read_pci_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline u8 dhar_valid(struct amd64_pvt *pvt)
{
	if (pvt->fam == 0x15 && pvt->model >= 0x30) {
		u32 tmp;
		amd64_read_pci_cfg(pvt->F1, DRAM_CONT_BASE, &tmp);
		return (tmp >> 1) & BIT(0);
	}
	return (pvt)->dhar & BIT(0);
}