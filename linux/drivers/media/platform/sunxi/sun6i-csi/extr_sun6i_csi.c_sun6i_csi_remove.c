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
struct sun6i_csi_dev {int /*<<< orphan*/  csi; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct sun6i_csi_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sun6i_csi_v4l2_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sun6i_csi_remove(struct platform_device *pdev)
{
	struct sun6i_csi_dev *sdev = platform_get_drvdata(pdev);

	sun6i_csi_v4l2_cleanup(&sdev->csi);

	return 0;
}