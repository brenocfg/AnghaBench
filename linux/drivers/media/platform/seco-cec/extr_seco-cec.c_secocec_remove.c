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
struct secocec_data {int /*<<< orphan*/  cec_adap; int /*<<< orphan*/  notifier; scalar_t__ ir; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRA_SMB_BASE_ADDR ; 
 int /*<<< orphan*/  SECOCEC_ENABLE_REG_1 ; 
 int SECOCEC_ENABLE_REG_1_IR ; 
 int /*<<< orphan*/  cec_notifier_cec_adap_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct secocec_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smb_rd16 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  smb_wr16 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int secocec_remove(struct platform_device *pdev)
{
	struct secocec_data *secocec = platform_get_drvdata(pdev);
	u16 val;

	if (secocec->ir) {
		smb_rd16(SECOCEC_ENABLE_REG_1, &val);

		smb_wr16(SECOCEC_ENABLE_REG_1, val & ~SECOCEC_ENABLE_REG_1_IR);

		dev_dbg(&pdev->dev, "IR disabled");
	}
	cec_notifier_cec_adap_unregister(secocec->notifier);
	cec_unregister_adapter(secocec->cec_adap);

	release_region(BRA_SMB_BASE_ADDR, 7);

	dev_dbg(&pdev->dev, "CEC device removed");

	return 0;
}