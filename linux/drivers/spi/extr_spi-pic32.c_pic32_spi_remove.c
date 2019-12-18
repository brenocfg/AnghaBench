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
struct pic32_spi {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic32_spi_disable (struct pic32_spi*) ; 
 int /*<<< orphan*/  pic32_spi_dma_unprep (struct pic32_spi*) ; 
 struct pic32_spi* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pic32_spi_remove(struct platform_device *pdev)
{
	struct pic32_spi *pic32s;

	pic32s = platform_get_drvdata(pdev);
	pic32_spi_disable(pic32s);
	clk_disable_unprepare(pic32s->clk);
	pic32_spi_dma_unprep(pic32s);

	return 0;
}