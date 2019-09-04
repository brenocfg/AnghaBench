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
struct device {int dummy; } ;
struct cxl {struct cxl* native; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_remove_adapter_nr (struct cxl*) ; 
 int /*<<< orphan*/  kfree (struct cxl*) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 
 struct cxl* to_cxl_adapter (struct device*) ; 

__attribute__((used)) static void cxl_release_adapter(struct device *dev)
{
	struct cxl *adapter = to_cxl_adapter(dev);

	pr_devel("cxl_release_adapter\n");

	cxl_remove_adapter_nr(adapter);

	kfree(adapter->native);
	kfree(adapter);
}