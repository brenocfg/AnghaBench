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
struct dwc3_ep {int dummy; } ;
struct dwc3 {int num_eps; struct dwc3_ep** eps; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc3_debugfs_create_endpoint_dir (struct dwc3_ep*,struct dentry*) ; 

__attribute__((used)) static void dwc3_debugfs_create_endpoint_dirs(struct dwc3 *dwc,
		struct dentry *parent)
{
	int			i;

	for (i = 0; i < dwc->num_eps; i++) {
		struct dwc3_ep	*dep = dwc->eps[i];

		if (!dep)
			continue;

		dwc3_debugfs_create_endpoint_dir(dep, parent);
	}
}