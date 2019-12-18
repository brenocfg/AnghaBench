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
struct hinfc_host {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct hinfc_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int hisi_nfc_remove(struct platform_device *pdev)
{
	struct hinfc_host *host = platform_get_drvdata(pdev);

	nand_release(&host->chip);

	return 0;
}