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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct rpmsg_device {scalar_t__ src; scalar_t__ dst; TYPE_1__ id; } ;
struct rpmsg_channel_info {scalar_t__ src; scalar_t__ dst; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RPMSG_ADDR_ANY ; 
 int /*<<< orphan*/  RPMSG_NAME_SIZE ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rpmsg_device* to_rpmsg_device (struct device*) ; 

__attribute__((used)) static int rpmsg_device_match(struct device *dev, void *data)
{
	struct rpmsg_channel_info *chinfo = data;
	struct rpmsg_device *rpdev = to_rpmsg_device(dev);

	if (chinfo->src != RPMSG_ADDR_ANY && chinfo->src != rpdev->src)
		return 0;

	if (chinfo->dst != RPMSG_ADDR_ANY && chinfo->dst != rpdev->dst)
		return 0;

	if (strncmp(chinfo->name, rpdev->id.name, RPMSG_NAME_SIZE))
		return 0;

	/* found a match ! */
	return 1;
}