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
struct rpmsg_endpoint {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct rpmsg_device {int /*<<< orphan*/  src; TYPE_1__ id; } ;
struct rpmsg_channel_info {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPMSG_ADDR_ANY ; 
 int /*<<< orphan*/  RPMSG_NAME_SIZE ; 
 int /*<<< orphan*/  cros_ec_rpmsg_callback ; 
 struct rpmsg_endpoint* rpmsg_create_ept (struct rpmsg_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct rpmsg_channel_info) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpmsg_endpoint *
cros_ec_rpmsg_create_ept(struct rpmsg_device *rpdev)
{
	struct rpmsg_channel_info chinfo = {};

	strscpy(chinfo.name, rpdev->id.name, RPMSG_NAME_SIZE);
	chinfo.src = rpdev->src;
	chinfo.dst = RPMSG_ADDR_ANY;

	return rpmsg_create_ept(rpdev, cros_ec_rpmsg_callback, NULL, chinfo);
}