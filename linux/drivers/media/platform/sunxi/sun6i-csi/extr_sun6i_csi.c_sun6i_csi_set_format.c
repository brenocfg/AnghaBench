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
struct TYPE_2__ {scalar_t__ field; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  code; } ;
struct sun6i_csi {TYPE_1__ config; } ;
struct sun6i_csi_dev {int /*<<< orphan*/  regmap; struct sun6i_csi csi; } ;

/* Variables and functions */
 int CSI_CH_CFG_FIELD_SEL_BOTH ; 
 int CSI_CH_CFG_FIELD_SEL_FIELD0 ; 
 int CSI_CH_CFG_FIELD_SEL_FIELD1 ; 
 int CSI_CH_CFG_FIELD_SEL_MASK ; 
 int CSI_CH_CFG_HFLIP_EN ; 
 int CSI_CH_CFG_INPUT_FMT (int) ; 
 int CSI_CH_CFG_INPUT_FMT_MASK ; 
 int CSI_CH_CFG_INPUT_SEQ (int) ; 
 int CSI_CH_CFG_INPUT_SEQ_MASK ; 
 int CSI_CH_CFG_OUTPUT_FMT (int) ; 
 int CSI_CH_CFG_OUTPUT_FMT_MASK ; 
 int /*<<< orphan*/  CSI_CH_CFG_REG ; 
 int CSI_CH_CFG_VFLIP_EN ; 
 scalar_t__ V4L2_FIELD_BOTTOM ; 
 scalar_t__ V4L2_FIELD_TOP ; 
 int get_csi_input_format (struct sun6i_csi_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_csi_input_seq (struct sun6i_csi_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_csi_output_format (struct sun6i_csi_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sun6i_csi_set_format(struct sun6i_csi_dev *sdev)
{
	struct sun6i_csi *csi = &sdev->csi;
	u32 cfg;
	u32 val;

	regmap_read(sdev->regmap, CSI_CH_CFG_REG, &cfg);

	cfg &= ~(CSI_CH_CFG_INPUT_FMT_MASK |
		 CSI_CH_CFG_OUTPUT_FMT_MASK | CSI_CH_CFG_VFLIP_EN |
		 CSI_CH_CFG_HFLIP_EN | CSI_CH_CFG_FIELD_SEL_MASK |
		 CSI_CH_CFG_INPUT_SEQ_MASK);

	val = get_csi_input_format(sdev, csi->config.code,
				   csi->config.pixelformat);
	cfg |= CSI_CH_CFG_INPUT_FMT(val);

	val = get_csi_output_format(sdev, csi->config.pixelformat,
				    csi->config.field);
	cfg |= CSI_CH_CFG_OUTPUT_FMT(val);

	val = get_csi_input_seq(sdev, csi->config.code,
				csi->config.pixelformat);
	cfg |= CSI_CH_CFG_INPUT_SEQ(val);

	if (csi->config.field == V4L2_FIELD_TOP)
		cfg |= CSI_CH_CFG_FIELD_SEL_FIELD0;
	else if (csi->config.field == V4L2_FIELD_BOTTOM)
		cfg |= CSI_CH_CFG_FIELD_SEL_FIELD1;
	else
		cfg |= CSI_CH_CFG_FIELD_SEL_BOTH;

	regmap_write(sdev->regmap, CSI_CH_CFG_REG, cfg);
}