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
struct sdw_port_runtime {int /*<<< orphan*/  num; int /*<<< orphan*/  ch_mask; } ;
struct sdw_port_config {int /*<<< orphan*/  num; int /*<<< orphan*/  ch_mask; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sdw_port_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sdw_port_runtime
*sdw_port_alloc(struct device *dev,
		struct sdw_port_config *port_config,
		int port_index)
{
	struct sdw_port_runtime *p_rt;

	p_rt = kzalloc(sizeof(*p_rt), GFP_KERNEL);
	if (!p_rt)
		return NULL;

	p_rt->ch_mask = port_config[port_index].ch_mask;
	p_rt->num = port_config[port_index].num;

	return p_rt;
}