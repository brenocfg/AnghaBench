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
struct v4l2_subdev {int dummy; } ;
struct imx214 {int streaming; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int imx214_start_streaming (struct imx214*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 struct imx214* to_imx214 (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx214_s_stream(struct v4l2_subdev *subdev, int enable)
{
	struct imx214 *imx214 = to_imx214(subdev);
	int ret;

	if (imx214->streaming == enable)
		return 0;

	if (enable) {
		ret = pm_runtime_get_sync(imx214->dev);
		if (ret < 0) {
			pm_runtime_put_noidle(imx214->dev);
			return ret;
		}

		ret = imx214_start_streaming(imx214);
		if (ret < 0)
			goto err_rpm_put;
	} else {
		ret = imx214_start_streaming(imx214);
		if (ret < 0)
			goto err_rpm_put;
		pm_runtime_put(imx214->dev);
	}

	imx214->streaming = enable;
	return 0;

err_rpm_put:
	pm_runtime_put(imx214->dev);
	return ret;
}