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
 unsigned long ENSD0 ; 
 unsigned long GPSELD ; 
 int /*<<< orphan*/  REG_MFSEL ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  mfp_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

void mfp_set_groupd(struct device *dev, const char *subname)
{
	unsigned long mfpen;
	const char *dev_id;

	BUG_ON((!dev) && (!subname));

	mutex_lock(&mfp_mutex);

	if (subname != NULL)
		dev_id = subname;
	else
		dev_id = dev_name(dev);

	mfpen = __raw_readl(REG_MFSEL);

	if (strcmp(dev_id, "nuc900-mmc-port0") == 0) {
		mfpen &= ~GPSELD;/*enable sd0*/
		mfpen |= ENSD0;
	} else
		mfpen &= (~GPSELD);

	__raw_writel(mfpen, REG_MFSEL);

	mutex_unlock(&mfp_mutex);
}