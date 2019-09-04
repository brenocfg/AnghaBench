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
struct mtk_jpeg_dev {int /*<<< orphan*/  larb; int /*<<< orphan*/  clk_jdec_smi; int /*<<< orphan*/  clk_jdec; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_smi_larb_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_jpeg_clk_off(struct mtk_jpeg_dev *jpeg)
{
	clk_disable_unprepare(jpeg->clk_jdec);
	clk_disable_unprepare(jpeg->clk_jdec_smi);
	mtk_smi_larb_put(jpeg->larb);
}