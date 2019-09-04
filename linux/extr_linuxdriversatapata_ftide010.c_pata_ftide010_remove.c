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
struct ftide010 {int /*<<< orphan*/  pclk; int /*<<< orphan*/  host; } ;
struct ata_host {struct ftide010* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ata_host_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct ata_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pata_ftide010_remove(struct platform_device *pdev)
{
	struct ata_host *host = platform_get_drvdata(pdev);
	struct ftide010 *ftide = host->private_data;

	ata_host_detach(ftide->host);
	if (!IS_ERR(ftide->pclk))
		clk_disable_unprepare(ftide->pclk);

	return 0;
}