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
struct sdw_stream_runtime {int /*<<< orphan*/  state; int /*<<< orphan*/  name; } ;
struct sdw_stream_config {int dummy; } ;
struct sdw_slave_runtime {int /*<<< orphan*/  m_rt_node; } ;
struct sdw_slave {TYPE_1__* bus; int /*<<< orphan*/  dev; } ;
struct sdw_port_config {int dummy; } ;
struct sdw_master_runtime {int /*<<< orphan*/  slave_rt_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SDW_STREAM_CONFIGURED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sdw_master_runtime* sdw_alloc_master_rt (TYPE_1__*,struct sdw_stream_config*,struct sdw_stream_runtime*) ; 
 struct sdw_slave_runtime* sdw_alloc_slave_rt (struct sdw_slave*,struct sdw_stream_config*,struct sdw_stream_runtime*) ; 
 int sdw_config_stream (int /*<<< orphan*/ *,struct sdw_stream_runtime*,struct sdw_stream_config*,int) ; 
 int /*<<< orphan*/  sdw_release_master_stream (struct sdw_master_runtime*,struct sdw_stream_runtime*) ; 
 int sdw_slave_port_config (struct sdw_slave*,struct sdw_slave_runtime*,struct sdw_port_config*,unsigned int) ; 

int sdw_stream_add_slave(struct sdw_slave *slave,
			 struct sdw_stream_config *stream_config,
			 struct sdw_port_config *port_config,
			 unsigned int num_ports,
			 struct sdw_stream_runtime *stream)
{
	struct sdw_slave_runtime *s_rt;
	struct sdw_master_runtime *m_rt;
	int ret;

	mutex_lock(&slave->bus->bus_lock);

	/*
	 * If this API is invoked by Slave first then m_rt is not valid.
	 * So, allocate m_rt and add Slave to it.
	 */
	m_rt = sdw_alloc_master_rt(slave->bus, stream_config, stream);
	if (!m_rt) {
		dev_err(&slave->dev,
			"alloc master runtime failed for stream:%s\n",
			stream->name);
		ret = -ENOMEM;
		goto error;
	}

	s_rt = sdw_alloc_slave_rt(slave, stream_config, stream);
	if (!s_rt) {
		dev_err(&slave->dev,
			"Slave runtime config failed for stream:%s\n",
			stream->name);
		ret = -ENOMEM;
		goto stream_error;
	}

	ret = sdw_config_stream(&slave->dev, stream, stream_config, true);
	if (ret)
		goto stream_error;

	list_add_tail(&s_rt->m_rt_node, &m_rt->slave_rt_list);

	ret = sdw_slave_port_config(slave, s_rt, port_config, num_ports);
	if (ret)
		goto stream_error;

	/*
	 * Change stream state to CONFIGURED on first Slave add.
	 * Bus is not aware of number of Slave(s) in a stream at this
	 * point so cannot depend on all Slave(s) to be added in order to
	 * change stream state to CONFIGURED.
	 */
	stream->state = SDW_STREAM_CONFIGURED;
	goto error;

stream_error:
	/*
	 * we hit error so cleanup the stream, release all Slave(s) and
	 * Master runtime
	 */
	sdw_release_master_stream(m_rt, stream);
error:
	mutex_unlock(&slave->bus->bus_lock);
	return ret;
}