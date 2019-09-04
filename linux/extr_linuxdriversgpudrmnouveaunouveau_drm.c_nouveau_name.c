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
typedef  int /*<<< orphan*/  u64 ;
struct drm_device {int /*<<< orphan*/  dev; scalar_t__ pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_pci_name (scalar_t__) ; 
 int /*<<< orphan*/  nouveau_platform_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64
nouveau_name(struct drm_device *dev)
{
	if (dev->pdev)
		return nouveau_pci_name(dev->pdev);
	else
		return nouveau_platform_name(to_platform_device(dev->dev));
}