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
 int HDMI_HTPLG_INT_EN ; 
 int HDMI_PORD_INT_EN ; 
 int /*<<< orphan*/  RX_EVENT ; 
 int /*<<< orphan*/  mtk_cec_set_bits (struct mtk_cec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mtk_cec_htplg_irq_enable(struct mtk_cec *cec)
{
	mtk_cec_set_bits(cec, RX_EVENT, HDMI_PORD_INT_EN | HDMI_HTPLG_INT_EN);
}