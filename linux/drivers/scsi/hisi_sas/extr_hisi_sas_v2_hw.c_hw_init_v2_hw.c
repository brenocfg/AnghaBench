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
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  init_reg_v2_hw (struct hisi_hba*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int reset_hw_v2_hw (struct hisi_hba*) ; 

__attribute__((used)) static int hw_init_v2_hw(struct hisi_hba *hisi_hba)
{
	struct device *dev = hisi_hba->dev;
	int rc;

	rc = reset_hw_v2_hw(hisi_hba);
	if (rc) {
		dev_err(dev, "hisi_sas_reset_hw failed, rc=%d", rc);
		return rc;
	}

	msleep(100);
	init_reg_v2_hw(hisi_hba);

	return 0;
}