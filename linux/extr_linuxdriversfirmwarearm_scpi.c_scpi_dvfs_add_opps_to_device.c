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
struct scpi_opp {int m_volt; int /*<<< orphan*/  freq; } ;
struct scpi_dvfs_info {int count; struct scpi_opp* opps; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (struct scpi_dvfs_info*) ; 
 int PTR_ERR (struct scpi_dvfs_info*) ; 
 int dev_pm_opp_add (struct device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_pm_opp_remove (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 struct scpi_dvfs_info* scpi_dvfs_info (struct device*) ; 

__attribute__((used)) static int scpi_dvfs_add_opps_to_device(struct device *dev)
{
	int idx, ret;
	struct scpi_opp *opp;
	struct scpi_dvfs_info *info = scpi_dvfs_info(dev);

	if (IS_ERR(info))
		return PTR_ERR(info);

	if (!info->opps)
		return -EIO;

	for (opp = info->opps, idx = 0; idx < info->count; idx++, opp++) {
		ret = dev_pm_opp_add(dev, opp->freq, opp->m_volt * 1000);
		if (ret) {
			dev_warn(dev, "failed to add opp %uHz %umV\n",
				 opp->freq, opp->m_volt);
			while (idx-- > 0)
				dev_pm_opp_remove(dev, (--opp)->freq);
			return ret;
		}
	}
	return 0;
}