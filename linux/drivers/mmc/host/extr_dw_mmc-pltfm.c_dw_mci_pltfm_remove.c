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
struct dw_mci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_mci_remove (struct dw_mci*) ; 
 struct dw_mci* platform_get_drvdata (struct platform_device*) ; 

int dw_mci_pltfm_remove(struct platform_device *pdev)
{
	struct dw_mci *host = platform_get_drvdata(pdev);

	dw_mci_remove(host);
	return 0;
}