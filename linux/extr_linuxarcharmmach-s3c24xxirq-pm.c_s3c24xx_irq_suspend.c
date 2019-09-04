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

/* Variables and functions */
 unsigned int ARRAY_SIZE (void**) ; 
 scalar_t__ S3C24XX_EINFLT0 ; 
 scalar_t__ S3C24XX_EINTMASK ; 
 scalar_t__ S3C24XX_EXTINT0 ; 
 void* __raw_readl (scalar_t__) ; 
 void** irq_save ; 
 int /*<<< orphan*/  s3c_pm_do_save (void**,unsigned int) ; 
 void** save_eintflt ; 
 void* save_eintmask ; 
 void** save_extint ; 

__attribute__((used)) static int s3c24xx_irq_suspend(void)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(save_extint); i++)
		save_extint[i] = __raw_readl(S3C24XX_EXTINT0 + (i*4));

	for (i = 0; i < ARRAY_SIZE(save_eintflt); i++)
		save_eintflt[i] = __raw_readl(S3C24XX_EINFLT0 + (i*4));

	s3c_pm_do_save(irq_save, ARRAY_SIZE(irq_save));
	save_eintmask = __raw_readl(S3C24XX_EINTMASK);

	return 0;
}