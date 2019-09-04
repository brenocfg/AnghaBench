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
 int CEC_32K_PDN ; 
 int /*<<< orphan*/  CEC_CKGEN ; 
 int HDMI_HTPLG_INT_32K_CLR ; 
 int HDMI_HTPLG_INT_32K_EN ; 
 int HDMI_PORD_INT_32K_CLR ; 
 int HDMI_PORD_INT_32K_EN ; 
 int PDN ; 
 int /*<<< orphan*/  RX_GEN_WD ; 
 int RX_INT_32K_CLR ; 
 int RX_INT_32K_EN ; 
 int /*<<< orphan*/  mtk_cec_mask (struct mtk_cec*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mtk_cec_set_bits (struct mtk_cec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mtk_cec_htplg_irq_init(struct mtk_cec *cec)
{
	mtk_cec_mask(cec, CEC_CKGEN, 0 | CEC_32K_PDN, PDN | CEC_32K_PDN);
	mtk_cec_set_bits(cec, RX_GEN_WD, HDMI_PORD_INT_32K_CLR |
			 RX_INT_32K_CLR | HDMI_HTPLG_INT_32K_CLR);
	mtk_cec_mask(cec, RX_GEN_WD, 0, HDMI_PORD_INT_32K_CLR | RX_INT_32K_CLR |
		     HDMI_HTPLG_INT_32K_CLR | HDMI_PORD_INT_32K_EN |
		     RX_INT_32K_EN | HDMI_HTPLG_INT_32K_EN);
}