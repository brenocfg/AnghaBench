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
typedef  size_t u8 ;
typedef  int u32 ;
struct amd64_pvt {TYPE_1__* csels; } ;
struct TYPE_2__ {int* csbases; int* csmasks; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*,int,int) ; 

__attribute__((used)) static int f17_base_addr_to_cs_size(struct amd64_pvt *pvt, u8 umc,
				    unsigned int cs_mode, int csrow_nr)
{
	u32 base_addr = pvt->csels[umc].csbases[csrow_nr];

	/*  Each mask is used for every two base addresses. */
	u32 addr_mask = pvt->csels[umc].csmasks[csrow_nr >> 1];

	/*  Register [31:1] = Address [39:9]. Size is in kBs here. */
	u32 size = ((addr_mask >> 1) - (base_addr >> 1) + 1) >> 1;

	edac_dbg(1, "BaseAddr: 0x%x, AddrMask: 0x%x\n", base_addr, addr_mask);

	/* Return size in MBs. */
	return size >> 10;
}