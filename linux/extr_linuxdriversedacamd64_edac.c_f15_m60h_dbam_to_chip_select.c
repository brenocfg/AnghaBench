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
struct amd64_pvt {scalar_t__ dram_type; TYPE_1__* csels; } ;
struct TYPE_2__ {int* csmasks; } ;

/* Variables and functions */
 scalar_t__ MEM_DDR4 ; 
 scalar_t__ MEM_LRDDR3 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int ddr3_cs_size (unsigned int,int) ; 
 int ddr3_lrdimm_cs_size (unsigned int,unsigned int) ; 
 int ddr4_cs_size (unsigned int) ; 

__attribute__((used)) static int f15_m60h_dbam_to_chip_select(struct amd64_pvt *pvt, u8 dct,
					unsigned cs_mode, int cs_mask_nr)
{
	int cs_size;
	u32 dcsm = pvt->csels[dct].csmasks[cs_mask_nr];

	WARN_ON(cs_mode > 12);

	if (pvt->dram_type == MEM_DDR4) {
		if (cs_mode > 9)
			return -1;

		cs_size = ddr4_cs_size(cs_mode);
	} else if (pvt->dram_type == MEM_LRDDR3) {
		unsigned rank_multiply = dcsm & 0xf;

		if (rank_multiply == 3)
			rank_multiply = 4;
		cs_size = ddr3_lrdimm_cs_size(cs_mode, rank_multiply);
	} else {
		/* Minimum cs size is 512mb for F15hM60h*/
		if (cs_mode == 0x1)
			return -1;

		cs_size = ddr3_cs_size(cs_mode, false);
	}

	return cs_size;
}