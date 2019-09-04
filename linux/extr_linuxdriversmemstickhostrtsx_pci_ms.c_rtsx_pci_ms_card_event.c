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
struct realtek_pci_ms {int /*<<< orphan*/  msh; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memstick_detect_change (int /*<<< orphan*/ ) ; 
 struct realtek_pci_ms* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void rtsx_pci_ms_card_event(struct platform_device *pdev)
{
	struct realtek_pci_ms *host = platform_get_drvdata(pdev);

	memstick_detect_change(host->msh);
}