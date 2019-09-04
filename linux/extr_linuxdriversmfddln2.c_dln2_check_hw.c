#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dln2_dev {TYPE_1__* interface; } ;
typedef  int /*<<< orphan*/  hw_type ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_DEVICE_VER ; 
 int /*<<< orphan*/  DLN2_HANDLE_CTRL ; 
 scalar_t__ DLN2_HW_ID ; 
 int ENODEV ; 
 int EREMOTEIO ; 
 int _dln2_transfer (struct dln2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dln2_check_hw(struct dln2_dev *dln2)
{
	int ret;
	__le32 hw_type;
	int len = sizeof(hw_type);

	ret = _dln2_transfer(dln2, DLN2_HANDLE_CTRL, CMD_GET_DEVICE_VER,
			     NULL, 0, &hw_type, &len);
	if (ret < 0)
		return ret;
	if (len < sizeof(hw_type))
		return -EREMOTEIO;

	if (le32_to_cpu(hw_type) != DLN2_HW_ID) {
		dev_err(&dln2->interface->dev, "Device ID 0x%x not supported\n",
			le32_to_cpu(hw_type));
		return -ENODEV;
	}

	return 0;
}