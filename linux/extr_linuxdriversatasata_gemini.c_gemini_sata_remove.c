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
struct sata_gemini {int /*<<< orphan*/  sata0_pclk; int /*<<< orphan*/  sata1_pclk; scalar_t__ sata_bridge; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 struct sata_gemini* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/ * sg_singleton ; 

__attribute__((used)) static int gemini_sata_remove(struct platform_device *pdev)
{
	struct sata_gemini *sg = platform_get_drvdata(pdev);

	if (sg->sata_bridge) {
		clk_unprepare(sg->sata1_pclk);
		clk_unprepare(sg->sata0_pclk);
	}
	sg_singleton = NULL;

	return 0;
}