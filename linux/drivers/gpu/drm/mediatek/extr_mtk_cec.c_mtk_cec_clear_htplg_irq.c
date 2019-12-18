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
struct mtk_cec {int dummy; } ;

/* Variables and functions */
 int CLEAR_CEC_IRQ ; 
 int HDMI_FULL_INT_CLR ; 
 int HDMI_HTPLG_INT_32K_CLR ; 
 int HDMI_HTPLG_INT_CLR ; 
 int HDMI_PORD_INT_32K_CLR ; 
 int HDMI_PORD_INT_CLR ; 
 int /*<<< orphan*/  NORMAL_INT_CTRL ; 
 int /*<<< orphan*/  RX_GEN_WD ; 
 int RX_INT_32K_CLR ; 
 int /*<<< orphan*/  TR_CONFIG ; 
 int /*<<< orphan*/  mtk_cec_clear_bits (struct mtk_cec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_cec_set_bits (struct mtk_cec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void mtk_cec_clear_htplg_irq(struct mtk_cec *cec)
{
	mtk_cec_set_bits(cec, TR_CONFIG, CLEAR_CEC_IRQ);
	mtk_cec_set_bits(cec, NORMAL_INT_CTRL, HDMI_HTPLG_INT_CLR |
			 HDMI_PORD_INT_CLR | HDMI_FULL_INT_CLR);
	mtk_cec_set_bits(cec, RX_GEN_WD, HDMI_PORD_INT_32K_CLR |
			 RX_INT_32K_CLR | HDMI_HTPLG_INT_32K_CLR);
	usleep_range(5, 10);
	mtk_cec_clear_bits(cec, NORMAL_INT_CTRL, HDMI_HTPLG_INT_CLR |
			   HDMI_PORD_INT_CLR | HDMI_FULL_INT_CLR);
	mtk_cec_clear_bits(cec, TR_CONFIG, CLEAR_CEC_IRQ);
	mtk_cec_clear_bits(cec, RX_GEN_WD, HDMI_PORD_INT_32K_CLR |
			   RX_INT_32K_CLR | HDMI_HTPLG_INT_32K_CLR);
}