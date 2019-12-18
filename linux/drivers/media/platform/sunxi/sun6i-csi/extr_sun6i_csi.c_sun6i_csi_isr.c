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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  video; } ;
struct sun6i_csi_dev {TYPE_1__ csi; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CSI_CH_INT_STA_FD_PD ; 
 int CSI_CH_INT_STA_FIFO0_OF_PD ; 
 int CSI_CH_INT_STA_FIFO1_OF_PD ; 
 int CSI_CH_INT_STA_FIFO2_OF_PD ; 
 int CSI_CH_INT_STA_HB_OF_PD ; 
 int /*<<< orphan*/  CSI_CH_INT_STA_REG ; 
 int /*<<< orphan*/  CSI_EN_CSI_EN ; 
 int /*<<< orphan*/  CSI_EN_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sun6i_video_frame_done (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sun6i_csi_isr(int irq, void *dev_id)
{
	struct sun6i_csi_dev *sdev = (struct sun6i_csi_dev *)dev_id;
	struct regmap *regmap = sdev->regmap;
	u32 status;

	regmap_read(regmap, CSI_CH_INT_STA_REG, &status);

	if (!(status & 0xFF))
		return IRQ_NONE;

	if ((status & CSI_CH_INT_STA_FIFO0_OF_PD) ||
	    (status & CSI_CH_INT_STA_FIFO1_OF_PD) ||
	    (status & CSI_CH_INT_STA_FIFO2_OF_PD) ||
	    (status & CSI_CH_INT_STA_HB_OF_PD)) {
		regmap_write(regmap, CSI_CH_INT_STA_REG, status);
		regmap_update_bits(regmap, CSI_EN_REG, CSI_EN_CSI_EN, 0);
		regmap_update_bits(regmap, CSI_EN_REG, CSI_EN_CSI_EN,
				   CSI_EN_CSI_EN);
		return IRQ_HANDLED;
	}

	if (status & CSI_CH_INT_STA_FD_PD)
		sun6i_video_frame_done(&sdev->csi.video);

	regmap_write(regmap, CSI_CH_INT_STA_REG, status);

	return IRQ_HANDLED;
}