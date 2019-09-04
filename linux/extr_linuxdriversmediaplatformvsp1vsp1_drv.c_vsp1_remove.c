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
struct vsp1_device {int /*<<< orphan*/  fcp; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct vsp1_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcar_fcp_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_destroy_entities (struct vsp1_device*) ; 

__attribute__((used)) static int vsp1_remove(struct platform_device *pdev)
{
	struct vsp1_device *vsp1 = platform_get_drvdata(pdev);

	vsp1_destroy_entities(vsp1);
	rcar_fcp_put(vsp1->fcp);

	pm_runtime_disable(&pdev->dev);

	return 0;
}