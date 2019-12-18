#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mdp5_kms {TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_INFO (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDP5_HW_VERSION_MAJOR ; 
 int /*<<< orphan*/  MDP5_HW_VERSION_MINOR ; 
 int /*<<< orphan*/  REG_MDP5_HW_VERSION ; 
 int /*<<< orphan*/  mdp5_read (struct mdp5_kms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 

__attribute__((used)) static void read_mdp_hw_revision(struct mdp5_kms *mdp5_kms,
				 u32 *major, u32 *minor)
{
	struct device *dev = &mdp5_kms->pdev->dev;
	u32 version;

	pm_runtime_get_sync(dev);
	version = mdp5_read(mdp5_kms, REG_MDP5_HW_VERSION);
	pm_runtime_put_sync(dev);

	*major = FIELD(version, MDP5_HW_VERSION_MAJOR);
	*minor = FIELD(version, MDP5_HW_VERSION_MINOR);

	DRM_DEV_INFO(dev, "MDP5 version v%d.%d", *major, *minor);
}