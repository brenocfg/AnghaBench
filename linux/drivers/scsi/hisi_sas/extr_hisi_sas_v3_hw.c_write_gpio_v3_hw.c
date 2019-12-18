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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hisi_hba {int /*<<< orphan*/  n_phy; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SAS_GPIO_REG_TX 128 
 int /*<<< orphan*/  SAS_GPIO_TX_0_1 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_gpio_v3_hw(struct hisi_hba *hisi_hba, u8 reg_type,
			u8 reg_index, u8 reg_count, u8 *write_data)
{
	struct device *dev = hisi_hba->dev;
	u32 *data = (u32 *)write_data;
	int i;

	switch (reg_type) {
	case SAS_GPIO_REG_TX:
		if ((reg_index + reg_count) > ((hisi_hba->n_phy + 3) / 4)) {
			dev_err(dev, "write gpio: invalid reg range[%d, %d]\n",
				reg_index, reg_index + reg_count - 1);
			return -EINVAL;
		}

		for (i = 0; i < reg_count; i++)
			hisi_sas_write32(hisi_hba,
					 SAS_GPIO_TX_0_1 + (reg_index + i) * 4,
					 data[i]);
		break;
	default:
		dev_err(dev, "write gpio: unsupported or bad reg type %d\n",
			reg_type);
		return -EINVAL;
	}

	return 0;
}