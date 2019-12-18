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
struct bcm47xxsflash {int /*<<< orphan*/  window; int /*<<< orphan*/  mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct bcm47xxsflash* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int bcm47xxsflash_bcma_remove(struct platform_device *pdev)
{
	struct bcm47xxsflash *b47s = platform_get_drvdata(pdev);

	mtd_device_unregister(&b47s->mtd);
	iounmap(b47s->window);

	return 0;
}