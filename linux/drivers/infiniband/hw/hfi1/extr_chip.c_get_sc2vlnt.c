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
typedef  scalar_t__ u64 ;
struct sc2vlnt {int* vlnt; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCC_CFG_SC_VL_TABLE_15_0 ; 
 int /*<<< orphan*/  DCC_CFG_SC_VL_TABLE_31_16 ; 
 scalar_t__ read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_sc2vlnt(struct hfi1_devdata *dd, struct sc2vlnt *dp)
{
	u64 reg;
	int i;

	/* each register contains 16 SC->VLnt mappings, 4 bits each */
	reg = read_csr(dd, DCC_CFG_SC_VL_TABLE_15_0);
	for (i = 0; i < sizeof(u64); i++) {
		u8 byte = *(((u8 *)&reg) + i);

		dp->vlnt[2 * i] = byte & 0xf;
		dp->vlnt[(2 * i) + 1] = (byte & 0xf0) >> 4;
	}

	reg = read_csr(dd, DCC_CFG_SC_VL_TABLE_31_16);
	for (i = 0; i < sizeof(u64); i++) {
		u8 byte = *(((u8 *)&reg) + i);

		dp->vlnt[16 + (2 * i)] = byte & 0xf;
		dp->vlnt[16 + (2 * i) + 1] = (byte & 0xf0) >> 4;
	}
	return sizeof(struct sc2vlnt);
}