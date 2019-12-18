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
struct TYPE_2__ {struct device_node* of_node; } ;
struct rpmsg_device {TYPE_1__ dev; int /*<<< orphan*/  ept; } ;
struct qcom_glink {scalar_t__ intentless; } ;
struct property {int length; int /*<<< orphan*/ * value; } ;
struct glink_core_rx_intent {int dummy; } ;
struct glink_channel {struct qcom_glink* glink; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int SZ_1K ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qcom_glink_advertise_intent (struct qcom_glink*,struct glink_channel*,struct glink_core_rx_intent*) ; 
 struct glink_core_rx_intent* qcom_glink_alloc_intent (struct qcom_glink*,struct glink_channel*,int,int) ; 
 struct glink_channel* to_glink_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_glink_announce_create(struct rpmsg_device *rpdev)
{
	struct glink_channel *channel = to_glink_channel(rpdev->ept);
	struct device_node *np = rpdev->dev.of_node;
	struct qcom_glink *glink = channel->glink;
	struct glink_core_rx_intent *intent;
	const struct property *prop = NULL;
	__be32 defaults[] = { cpu_to_be32(SZ_1K), cpu_to_be32(5) };
	int num_intents;
	int num_groups = 1;
	__be32 *val = defaults;
	int size;

	if (glink->intentless)
		return 0;

	prop = of_find_property(np, "qcom,intents", NULL);
	if (prop) {
		val = prop->value;
		num_groups = prop->length / sizeof(u32) / 2;
	}

	/* Channel is now open, advertise base set of intents */
	while (num_groups--) {
		size = be32_to_cpup(val++);
		num_intents = be32_to_cpup(val++);
		while (num_intents--) {
			intent = qcom_glink_alloc_intent(glink, channel, size,
							 true);
			if (!intent)
				break;

			qcom_glink_advertise_intent(glink, channel, intent);
		}
	}
	return 0;
}