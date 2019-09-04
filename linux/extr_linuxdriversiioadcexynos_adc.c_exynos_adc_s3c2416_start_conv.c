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
typedef  unsigned long u32 ;
struct exynos_adc {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 unsigned long ADC_CON_EN_START ; 
 int /*<<< orphan*/  ADC_S3C2410_MUX (int /*<<< orphan*/ ) ; 
 unsigned long ADC_S3C2416_CON_RES_SEL ; 
 int /*<<< orphan*/  ADC_V1_CON (int /*<<< orphan*/ ) ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_adc_s3c2416_start_conv(struct exynos_adc *info,
					  unsigned long addr)
{
	u32 con1;

	/* Enable 12 bit ADC resolution */
	con1 = readl(ADC_V1_CON(info->regs));
	con1 |= ADC_S3C2416_CON_RES_SEL;
	writel(con1, ADC_V1_CON(info->regs));

	/* Select channel for S3C2416 */
	writel(addr, ADC_S3C2410_MUX(info->regs));

	con1 = readl(ADC_V1_CON(info->regs));
	writel(con1 | ADC_CON_EN_START, ADC_V1_CON(info->regs));
}