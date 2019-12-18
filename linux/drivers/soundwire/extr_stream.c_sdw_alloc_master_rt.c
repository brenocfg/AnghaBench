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
struct sdw_stream_runtime {int /*<<< orphan*/  master_list; } ;
struct sdw_stream_config {int /*<<< orphan*/  direction; int /*<<< orphan*/  ch_count; } ;
struct sdw_master_runtime {int /*<<< orphan*/  direction; struct sdw_stream_runtime* stream; struct sdw_bus* bus; int /*<<< orphan*/  ch_count; int /*<<< orphan*/  bus_node; int /*<<< orphan*/  stream_node; int /*<<< orphan*/  slave_rt_list; int /*<<< orphan*/  port_list; } ;
struct sdw_bus {int /*<<< orphan*/  m_rt_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct sdw_master_runtime* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sdw_master_runtime* sdw_find_master_rt (struct sdw_bus*,struct sdw_stream_runtime*) ; 

__attribute__((used)) static struct sdw_master_runtime
*sdw_alloc_master_rt(struct sdw_bus *bus,
		     struct sdw_stream_config *stream_config,
		     struct sdw_stream_runtime *stream)
{
	struct sdw_master_runtime *m_rt;

	/*
	 * check if Master is already allocated (as a result of Slave adding
	 * it first), if so skip allocation and go to configure
	 */
	m_rt = sdw_find_master_rt(bus, stream);
	if (m_rt)
		goto stream_config;

	m_rt = kzalloc(sizeof(*m_rt), GFP_KERNEL);
	if (!m_rt)
		return NULL;

	/* Initialization of Master runtime handle */
	INIT_LIST_HEAD(&m_rt->port_list);
	INIT_LIST_HEAD(&m_rt->slave_rt_list);
	list_add_tail(&m_rt->stream_node, &stream->master_list);

	list_add_tail(&m_rt->bus_node, &bus->m_rt_list);

stream_config:
	m_rt->ch_count = stream_config->ch_count;
	m_rt->bus = bus;
	m_rt->stream = stream;
	m_rt->direction = stream_config->direction;

	return m_rt;
}