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

/* Variables and functions */
 unsigned int CDRATIO_x1 ; 
 unsigned int CDRATIO_x2 ; 
 unsigned int CDRATIO_x4 ; 
 unsigned int CFGWDTH_32 ; 

__attribute__((used)) static unsigned int socfpga_a10_fpga_get_cd_ratio(unsigned int cfg_width,
						  bool encrypt, bool compress)
{
	unsigned int cd_ratio;

	/*
	 * cd ratio is dependent on cfg width and whether the bitstream
	 * is encrypted and/or compressed.
	 *
	 * | width | encr. | compr. | cd ratio |
	 * |  16   |   0   |   0    |     1    |
	 * |  16   |   0   |   1    |     4    |
	 * |  16   |   1   |   0    |     2    |
	 * |  16   |   1   |   1    |     4    |
	 * |  32   |   0   |   0    |     1    |
	 * |  32   |   0   |   1    |     8    |
	 * |  32   |   1   |   0    |     4    |
	 * |  32   |   1   |   1    |     8    |
	 */
	if (!compress && !encrypt)
		return CDRATIO_x1;

	if (compress)
		cd_ratio = CDRATIO_x4;
	else
		cd_ratio = CDRATIO_x2;

	/* If 32 bit, double the cd ratio by incrementing the field  */
	if (cfg_width == CFGWDTH_32)
		cd_ratio += 1;

	return cd_ratio;
}