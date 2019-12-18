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
struct bgmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bgmac_enet_remove (struct bgmac*) ; 
 struct bgmac* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int bgmac_remove(struct platform_device *pdev)
{
	struct bgmac *bgmac = platform_get_drvdata(pdev);

	bgmac_enet_remove(bgmac);

	return 0;
}