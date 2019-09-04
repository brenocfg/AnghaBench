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
struct platform_device {int dummy; } ;
struct csi2rx_priv {int /*<<< orphan*/  subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct csi2rx_priv*) ; 
 struct csi2rx_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int csi2rx_remove(struct platform_device *pdev)
{
	struct csi2rx_priv *csi2rx = platform_get_drvdata(pdev);

	v4l2_async_unregister_subdev(&csi2rx->subdev);
	kfree(csi2rx);

	return 0;
}