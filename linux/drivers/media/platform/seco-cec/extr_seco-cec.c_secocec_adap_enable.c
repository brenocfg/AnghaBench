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
typedef  int u16 ;
struct secocec_data {struct device* dev; } ;
struct device {int dummy; } ;
struct cec_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECOCEC_ENABLE_REG_1 ; 
 int SECOCEC_ENABLE_REG_1_CEC ; 
 int SECOCEC_ENABLE_REG_1_IR ; 
 int /*<<< orphan*/  SECOCEC_STATUS_REG_1 ; 
 struct secocec_data* cec_get_drvdata (struct cec_adapter*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int smb_rd16 (int /*<<< orphan*/ ,int*) ; 
 int smb_wr16 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int secocec_adap_enable(struct cec_adapter *adap, bool enable)
{
	struct secocec_data *cec = cec_get_drvdata(adap);
	struct device *dev = cec->dev;
	u16 val = 0;
	int status;

	if (enable) {
		/* Clear the status register */
		status = smb_rd16(SECOCEC_STATUS_REG_1, &val);
		if (status)
			goto err;

		status = smb_wr16(SECOCEC_STATUS_REG_1, val);
		if (status)
			goto err;

		/* Enable the interrupts */
		status = smb_rd16(SECOCEC_ENABLE_REG_1, &val);
		if (status)
			goto err;

		status = smb_wr16(SECOCEC_ENABLE_REG_1,
				  val | SECOCEC_ENABLE_REG_1_CEC);
		if (status)
			goto err;

		dev_dbg(dev, "Device enabled");
	} else {
		/* Clear the status register */
		status = smb_rd16(SECOCEC_STATUS_REG_1, &val);
		status = smb_wr16(SECOCEC_STATUS_REG_1, val);

		/* Disable the interrupts */
		status = smb_rd16(SECOCEC_ENABLE_REG_1, &val);
		status = smb_wr16(SECOCEC_ENABLE_REG_1, val &
				  ~SECOCEC_ENABLE_REG_1_CEC &
				  ~SECOCEC_ENABLE_REG_1_IR);

		dev_dbg(dev, "Device disabled");
	}

	return 0;
err:
	return status;
}