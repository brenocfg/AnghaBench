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
struct mtk_jpeg_dev {int /*<<< orphan*/  clk_jdec; int /*<<< orphan*/  clk_jdec_smi; int /*<<< orphan*/  dev; int /*<<< orphan*/  larb; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mtk_smi_larb_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_jpeg_clk_on(struct mtk_jpeg_dev *jpeg)
{
	int ret;

	ret = mtk_smi_larb_get(jpeg->larb);
	if (ret)
		dev_err(jpeg->dev, "mtk_smi_larb_get larbvdec fail %d\n", ret);
	clk_prepare_enable(jpeg->clk_jdec_smi);
	clk_prepare_enable(jpeg->clk_jdec);
}