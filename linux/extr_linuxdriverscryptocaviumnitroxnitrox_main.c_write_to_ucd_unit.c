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
typedef  int u64 ;
typedef  int u32 ;
struct ucode {int* code; int /*<<< orphan*/  code_size; } ;
struct TYPE_2__ {int se_cores; } ;
struct nitrox_device {TYPE_1__ hw; } ;

/* Variables and functions */
 int POM_GRP_EXECMASKX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SE_GROUP ; 
 int UCD_SE_EID_UCODE_BLOCK_NUMX (int) ; 
 int UCD_UCODE_LOAD_BLOCK_NUM ; 
 int UCD_UCODE_LOAD_IDX_DATAX (int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int,int) ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void write_to_ucd_unit(struct nitrox_device *ndev,
			      struct ucode *ucode)
{
	u32 code_size = be32_to_cpu(ucode->code_size) * 2;
	u64 offset, data;
	int i = 0;

	/*
	 * UCD structure
	 *
	 *  -------------
	 *  |    BLK 7  |
	 *  -------------
	 *  |    BLK 6  |
	 *  -------------
	 *  |    ...    |
	 *  -------------
	 *  |    BLK 0  |
	 *  -------------
	 *  Total of 8 blocks, each size 32KB
	 */

	/* set the block number */
	offset = UCD_UCODE_LOAD_BLOCK_NUM;
	nitrox_write_csr(ndev, offset, 0);

	code_size = roundup(code_size, 8);
	while (code_size) {
		data = ucode->code[i];
		/* write 8 bytes at a time */
		offset = UCD_UCODE_LOAD_IDX_DATAX(i);
		nitrox_write_csr(ndev, offset, data);
		code_size -= 8;
		i++;
	}

	/* put all SE cores in group 0 */
	offset = POM_GRP_EXECMASKX(SE_GROUP);
	nitrox_write_csr(ndev, offset, (~0ULL));

	for (i = 0; i < ndev->hw.se_cores; i++) {
		/*
		 * write block number and firware length
		 * bit:<2:0> block number
		 * bit:3 is set SE uses 32KB microcode
		 * bit:3 is clear SE uses 64KB microcode
		 */
		offset = UCD_SE_EID_UCODE_BLOCK_NUMX(i);
		nitrox_write_csr(ndev, offset, 0x8);
	}
	usleep_range(300, 400);
}