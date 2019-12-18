#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pr_aptpl_active; } ;
struct TYPE_4__ {int /*<<< orphan*/  emulate_pr; } ;
struct se_device {TYPE_3__ t10_pr; TYPE_2__* transport; TYPE_1__ dev_attrib; } ;
struct config_item {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {int transport_flags; } ;

/* Variables and functions */
 int TRANSPORT_FLAG_PASSTHROUGH_PGR ; 
 struct se_device* pr_to_dev (struct config_item*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t target_pr_res_aptpl_active_show(struct config_item *item,
		char *page)
{
	struct se_device *dev = pr_to_dev(item);

	if (!dev->dev_attrib.emulate_pr ||
	    (dev->transport->transport_flags & TRANSPORT_FLAG_PASSTHROUGH_PGR))
		return 0;

	return sprintf(page, "APTPL Bit Status: %s\n",
		(dev->t10_pr.pr_aptpl_active) ? "Activated" : "Disabled");
}