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
struct sun6i_csi_dev {int* planar_offset; int /*<<< orphan*/  regmap; } ;
struct sun6i_csi {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_CH_F0_BUFA_REG ; 
 int /*<<< orphan*/  CSI_CH_F1_BUFA_REG ; 
 int /*<<< orphan*/  CSI_CH_F2_BUFA_REG ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sun6i_csi_dev* sun6i_csi_to_dev (struct sun6i_csi*) ; 

void sun6i_csi_update_buf_addr(struct sun6i_csi *csi, dma_addr_t addr)
{
	struct sun6i_csi_dev *sdev = sun6i_csi_to_dev(csi);

	regmap_write(sdev->regmap, CSI_CH_F0_BUFA_REG,
		     (addr + sdev->planar_offset[0]) >> 2);
	if (sdev->planar_offset[1] != -1)
		regmap_write(sdev->regmap, CSI_CH_F1_BUFA_REG,
			     (addr + sdev->planar_offset[1]) >> 2);
	if (sdev->planar_offset[2] != -1)
		regmap_write(sdev->regmap, CSI_CH_F2_BUFA_REG,
			     (addr + sdev->planar_offset[2]) >> 2);
}