#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtl2832_sdr_platform_data {struct dvb_frontend* dvb_frontend; } ;
struct rtl2832_sdr_dev {struct platform_device* pdev; } ;
struct TYPE_6__ {struct rtl2832_sdr_platform_data* platform_data; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* init ) (struct dvb_frontend*) ;} ;
struct TYPE_4__ {TYPE_2__ tuner_ops; } ;
struct dvb_frontend {TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 

__attribute__((used)) static int rtl2832_sdr_set_tuner(struct rtl2832_sdr_dev *dev)
{
	struct platform_device *pdev = dev->pdev;
	struct rtl2832_sdr_platform_data *pdata = pdev->dev.platform_data;
	struct dvb_frontend *fe = pdata->dvb_frontend;

	dev_dbg(&pdev->dev, "\n");

	if (fe->ops.tuner_ops.init)
		fe->ops.tuner_ops.init(fe);

	return 0;
}