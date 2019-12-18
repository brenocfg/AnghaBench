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
struct sdw_stream_runtime {int dummy; } ;
struct sdw_stream_config {int /*<<< orphan*/  direction; int /*<<< orphan*/  ch_count; } ;
struct sdw_slave_runtime {struct sdw_slave* slave; int /*<<< orphan*/  direction; int /*<<< orphan*/  ch_count; int /*<<< orphan*/  port_list; } ;
struct sdw_slave {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct sdw_slave_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sdw_slave_runtime
*sdw_alloc_slave_rt(struct sdw_slave *slave,
		    struct sdw_stream_config *stream_config,
		    struct sdw_stream_runtime *stream)
{
	struct sdw_slave_runtime *s_rt;

	s_rt = kzalloc(sizeof(*s_rt), GFP_KERNEL);
	if (!s_rt)
		return NULL;

	INIT_LIST_HEAD(&s_rt->port_list);
	s_rt->ch_count = stream_config->ch_count;
	s_rt->direction = stream_config->direction;
	s_rt->slave = slave;

	return s_rt;
}