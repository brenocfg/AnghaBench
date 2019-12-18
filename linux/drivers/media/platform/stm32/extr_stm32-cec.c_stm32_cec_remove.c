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
struct stm32_cec {int /*<<< orphan*/  adap; int /*<<< orphan*/  clk_hdmi_cec; int /*<<< orphan*/  clk_cec; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct stm32_cec* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int stm32_cec_remove(struct platform_device *pdev)
{
	struct stm32_cec *cec = platform_get_drvdata(pdev);

	clk_unprepare(cec->clk_cec);
	clk_unprepare(cec->clk_hdmi_cec);

	cec_unregister_adapter(cec->adap);

	return 0;
}