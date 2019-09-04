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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long ENKPI ; 
 unsigned long ENNAND ; 
 unsigned long GPSELC ; 
 int /*<<< orphan*/  REG_MFSEL ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  mfp_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void mfp_set_groupc(struct device *dev)
{
	unsigned long mfpen;
	const char *dev_id;

	BUG_ON(!dev);

	mutex_lock(&mfp_mutex);

	dev_id = dev_name(dev);

	mfpen = __raw_readl(REG_MFSEL);

	if (strcmp(dev_id, "nuc900-lcd") == 0)
		mfpen |= GPSELC;/*enable lcd*/
	else if (strcmp(dev_id, "nuc900-kpi") == 0) {
		mfpen &= (~GPSELC);/*enable kpi*/
		mfpen |= ENKPI;
	} else if (strcmp(dev_id, "nuc900-nand") == 0) {
		mfpen &= (~GPSELC);/*enable nand*/
		mfpen |= ENNAND;
	} else
		mfpen &= (~GPSELC);/*GPIOC[14:0]*/

	__raw_writel(mfpen, REG_MFSEL);

	mutex_unlock(&mfp_mutex);
}