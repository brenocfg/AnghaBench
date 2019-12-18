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
struct npcm_fiu_spi {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct npcm_fiu_spi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int npcm_fiu_remove(struct platform_device *pdev)
{
	struct npcm_fiu_spi *fiu = platform_get_drvdata(pdev);

	clk_disable_unprepare(fiu->clk);
	return 0;
}