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
struct sun4i_tcon_quirks {int has_channel_0; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  sun4i_tcon_of_table ; 

__attribute__((used)) static bool sun4i_drv_node_is_tcon_with_ch0(struct device_node *node)
{
	const struct of_device_id *match;

	match = of_match_node(sun4i_tcon_of_table, node);
	if (match) {
		struct sun4i_tcon_quirks *quirks;

		quirks = (struct sun4i_tcon_quirks *)match->data;

		return quirks->has_channel_0;
	}

	return false;
}