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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  serial_no ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_GET_DEVICE_SN ; 
 int /*<<< orphan*/  DLN2_HANDLE_CTRL ; 
 int EREMOTEIO ; 
 int _dln2_transfer (struct dln2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dln2_print_serialno(struct dln2_dev *dln2)
{
	int ret;
	__le32 serial_no;
	int len = sizeof(serial_no);
	struct device *dev = &dln2->interface->dev;

	ret = _dln2_transfer(dln2, DLN2_HANDLE_CTRL, CMD_GET_DEVICE_SN, NULL, 0,
			     &serial_no, &len);
	if (ret < 0)
		return ret;
	if (len < sizeof(serial_no))
		return -EREMOTEIO;

	dev_info(dev, "Diolan DLN2 serial %u\n", le32_to_cpu(serial_no));

	return 0;
}