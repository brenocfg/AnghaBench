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
struct mtk_cec {scalar_t__ regs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int HDMI_HTPLG ; 
 unsigned int HDMI_PORD ; 
 scalar_t__ RX_EVENT ; 
 struct mtk_cec* dev_get_drvdata (struct device*) ; 
 unsigned int readl (scalar_t__) ; 

bool mtk_cec_hpd_high(struct device *dev)
{
	struct mtk_cec *cec = dev_get_drvdata(dev);
	unsigned int status;

	status = readl(cec->regs + RX_EVENT);

	return (status & (HDMI_PORD | HDMI_HTPLG)) == (HDMI_PORD | HDMI_HTPLG);
}