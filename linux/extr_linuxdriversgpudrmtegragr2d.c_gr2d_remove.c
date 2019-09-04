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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct gr2d {int /*<<< orphan*/  clk; TYPE_1__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int host1x_client_unregister (int /*<<< orphan*/ *) ; 
 struct gr2d* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int gr2d_remove(struct platform_device *pdev)
{
	struct gr2d *gr2d = platform_get_drvdata(pdev);
	int err;

	err = host1x_client_unregister(&gr2d->client.base);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		return err;
	}

	clk_disable_unprepare(gr2d->clk);

	return 0;
}