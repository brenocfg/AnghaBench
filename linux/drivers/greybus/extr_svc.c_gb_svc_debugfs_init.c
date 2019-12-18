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
struct gb_svc {int /*<<< orphan*/  dev; int /*<<< orphan*/  debugfs_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_debugfs_get () ; 
 int /*<<< orphan*/  gb_svc_pwrmon_debugfs_init (struct gb_svc*) ; 

__attribute__((used)) static void gb_svc_debugfs_init(struct gb_svc *svc)
{
	svc->debugfs_dentry = debugfs_create_dir(dev_name(&svc->dev),
						 gb_debugfs_get());
	gb_svc_pwrmon_debugfs_init(svc);
}