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
struct zd1301_demod_dev {struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dvb_frontend_tune_settings {int min_delay_ms; } ;
struct dvb_frontend {struct zd1301_demod_dev* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int zd1301_demod_get_tune_settings(struct dvb_frontend *fe,
					  struct dvb_frontend_tune_settings *settings)
{
	struct zd1301_demod_dev *dev = fe->demodulator_priv;
	struct platform_device *pdev = dev->pdev;

	dev_dbg(&pdev->dev, "\n");

	/* ~180ms seems to be enough */
	settings->min_delay_ms = 400;

	return 0;
}