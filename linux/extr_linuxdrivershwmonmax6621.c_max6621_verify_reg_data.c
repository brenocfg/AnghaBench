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
 int EIO ; 
 int EOPNOTSUPP ; 
#define  MAX6621_ALERT_DIS 132 
 int MAX6621_PECI_ERR_MAX ; 
 int MAX6621_PECI_ERR_MIN ; 
#define  MAX6621_POOL_DIS 131 
#define  MAX6621_POOL_UNCOMPLETE 130 
#define  MAX6621_SD_DIS 129 
#define  MAX6621_TRAN_FAILED 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 

__attribute__((used)) static int max6621_verify_reg_data(struct device *dev, int regval)
{
	if (regval >= MAX6621_PECI_ERR_MIN &&
	    regval <= MAX6621_PECI_ERR_MAX) {
		dev_dbg(dev, "PECI error code - err 0x%04x.\n",
			regval);

		return -EIO;
	}

	switch (regval) {
	case MAX6621_TRAN_FAILED:
		dev_dbg(dev, "PECI transaction failed - err 0x%04x.\n",
			regval);
		return -EIO;
	case MAX6621_POOL_DIS:
		dev_dbg(dev, "Polling disabled - err 0x%04x.\n", regval);
		return -EOPNOTSUPP;
	case MAX6621_POOL_UNCOMPLETE:
		dev_dbg(dev, "First poll not completed on startup - err 0x%04x.\n",
			regval);
		return -EIO;
	case MAX6621_SD_DIS:
		dev_dbg(dev, "Resource is disabled - err 0x%04x.\n", regval);
		return -EOPNOTSUPP;
	case MAX6621_ALERT_DIS:
		dev_dbg(dev, "No alert active - err 0x%04x.\n", regval);
		return -EOPNOTSUPP;
	default:
		return 0;
	}
}