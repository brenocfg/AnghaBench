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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct occ {int powr_sample_time_us; int poll_cmd_data; int /*<<< orphan*/  send_cmd; TYPE_1__* bus_dev; } ;
struct p9_sbe_occ {struct occ occ; int /*<<< orphan*/  sbe; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct p9_sbe_occ* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int occ_setup (struct occ*,char*) ; 
 int /*<<< orphan*/  p9_sbe_occ_send_cmd ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct occ*) ; 

__attribute__((used)) static int p9_sbe_occ_probe(struct platform_device *pdev)
{
	int rc;
	struct occ *occ;
	struct p9_sbe_occ *ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx),
					      GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->sbe = pdev->dev.parent;
	occ = &ctx->occ;
	occ->bus_dev = &pdev->dev;
	platform_set_drvdata(pdev, occ);

	occ->powr_sample_time_us = 500;
	occ->poll_cmd_data = 0x20;		/* P9 OCC poll data */
	occ->send_cmd = p9_sbe_occ_send_cmd;

	rc = occ_setup(occ, "p9_occ");
	if (rc == -ESHUTDOWN)
		rc = -ENODEV;	/* Host is shutdown, don't spew errors */

	return rc;
}