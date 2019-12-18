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
struct s3c_rtc {int /*<<< orphan*/  rtc_clk; int /*<<< orphan*/  rtc_src_clk; TYPE_1__* data; int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ needs_src_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct s3c_rtc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  s3c_rtc_setaie (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s3c_rtc_remove(struct platform_device *pdev)
{
	struct s3c_rtc *info = platform_get_drvdata(pdev);

	s3c_rtc_setaie(info->dev, 0);

	if (info->data->needs_src_clk)
		clk_unprepare(info->rtc_src_clk);
	clk_unprepare(info->rtc_clk);

	return 0;
}