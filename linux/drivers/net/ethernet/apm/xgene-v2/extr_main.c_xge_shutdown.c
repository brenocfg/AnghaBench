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
struct xge_pdata {int /*<<< orphan*/  ndev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct xge_pdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  xge_remove (struct platform_device*) ; 

__attribute__((used)) static void xge_shutdown(struct platform_device *pdev)
{
	struct xge_pdata *pdata;

	pdata = platform_get_drvdata(pdev);
	if (!pdata)
		return;

	if (!pdata->ndev)
		return;

	xge_remove(pdev);
}