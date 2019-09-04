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
struct adc_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C2410_ADCCON ; 
 scalar_t__ S3C2410_ADCDLY ; 
 scalar_t__ S3C2410_ADCTSC ; 
 int /*<<< orphan*/  adc_dbg (struct adc_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void s3c_adc_dbgshow(struct adc_device *adc)
{
	adc_dbg(adc, "CON=%08x, TSC=%08x, DLY=%08x\n",
		readl(adc->regs + S3C2410_ADCCON),
		readl(adc->regs + S3C2410_ADCTSC),
		readl(adc->regs + S3C2410_ADCDLY));
}