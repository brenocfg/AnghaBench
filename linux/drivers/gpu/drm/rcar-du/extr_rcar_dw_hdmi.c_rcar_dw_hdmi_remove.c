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
struct dw_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_hdmi_remove (struct dw_hdmi*) ; 
 struct dw_hdmi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int rcar_dw_hdmi_remove(struct platform_device *pdev)
{
	struct dw_hdmi *hdmi = platform_get_drvdata(pdev);

	dw_hdmi_remove(hdmi);

	return 0;
}