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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rmi_driver_data {scalar_t__ num_tx_electrodes; scalar_t__ num_rx_electrodes; } ;
struct rmi_device {int /*<<< orphan*/  dev; } ;
struct f54_data {int num_rx_electrodes; int num_tx_electrodes; int /*<<< orphan*/  input; TYPE_1__* fn; } ;
struct TYPE_2__ {struct rmi_device* rmi_dev; } ;

/* Variables and functions */
#define  F54_16BIT_IMAGE 133 
#define  F54_8BIT_IMAGE 132 
#define  F54_FULL_RAW_CAP 131 
#define  F54_FULL_RAW_CAP_RX_OFFSET_REMOVED 130 
#define  F54_RAW_16BIT_IMAGE 129 
#define  F54_TRUE_BASELINE 128 
 struct rmi_driver_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int rmi_f54_get_reptype (struct f54_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t rmi_f54_get_report_size(struct f54_data *f54)
{
	struct rmi_device *rmi_dev = f54->fn->rmi_dev;
	struct rmi_driver_data *drv_data = dev_get_drvdata(&rmi_dev->dev);
	u8 rx = drv_data->num_rx_electrodes ? : f54->num_rx_electrodes;
	u8 tx = drv_data->num_tx_electrodes ? : f54->num_tx_electrodes;
	size_t size;

	switch (rmi_f54_get_reptype(f54, f54->input)) {
	case F54_8BIT_IMAGE:
		size = rx * tx;
		break;
	case F54_16BIT_IMAGE:
	case F54_RAW_16BIT_IMAGE:
	case F54_TRUE_BASELINE:
	case F54_FULL_RAW_CAP:
	case F54_FULL_RAW_CAP_RX_OFFSET_REMOVED:
		size = sizeof(u16) * rx * tx;
		break;
	default:
		size = 0;
	}

	return size;
}