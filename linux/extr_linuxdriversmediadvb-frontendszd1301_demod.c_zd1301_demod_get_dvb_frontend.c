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
struct dvb_frontend {int dummy; } ;
struct zd1301_demod_dev {struct dvb_frontend frontend; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct zd1301_demod_dev* platform_get_drvdata (struct platform_device*) ; 

struct dvb_frontend *zd1301_demod_get_dvb_frontend(struct platform_device *pdev)
{
	struct zd1301_demod_dev *dev = platform_get_drvdata(pdev);

	dev_dbg(&pdev->dev, "\n");

	return &dev->frontend;
}