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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_PROBE_DELAY ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_probe(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "sleeping for %d msecs in probe\n",
		 TEST_PROBE_DELAY);
	msleep(TEST_PROBE_DELAY);
	dev_info(&pdev->dev, "done sleeping\n");

	return 0;
}