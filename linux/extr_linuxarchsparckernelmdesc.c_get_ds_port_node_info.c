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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
union md_node_info {TYPE_1__ ds_port; } ;
typedef  int /*<<< orphan*/  u64 ;
struct mdesc_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * mdesc_get_property (struct mdesc_handle*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_ds_port_node_info(struct mdesc_handle *md, u64 node,
				 union md_node_info *node_info)
{
	const u64 *idp;

	/* DS port nodes use the "id" property to distinguish them */
	idp = mdesc_get_property(md, node, "id", NULL);
	if (!idp)
		return -1;

	node_info->ds_port.id = *idp;

	return 0;
}