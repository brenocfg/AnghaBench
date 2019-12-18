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
struct TYPE_2__ {scalar_t__ rate; scalar_t__ bps; int /*<<< orphan*/  ch_count; } ;
struct sdw_stream_runtime {TYPE_1__ params; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct sdw_stream_config {scalar_t__ frame_rate; scalar_t__ bps; scalar_t__ ch_count; int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdw_config_stream(struct device *dev,
			     struct sdw_stream_runtime *stream,
			     struct sdw_stream_config *stream_config,
			     bool is_slave)
{
	/*
	 * Update the stream rate, channel and bps based on data
	 * source. For more than one data source (multilink),
	 * match the rate, bps, stream type and increment number of channels.
	 *
	 * If rate/bps is zero, it means the values are not set, so skip
	 * comparison and allow the value to be set and stored in stream
	 */
	if (stream->params.rate &&
	    stream->params.rate != stream_config->frame_rate) {
		dev_err(dev, "rate not matching, stream:%s\n", stream->name);
		return -EINVAL;
	}

	if (stream->params.bps &&
	    stream->params.bps != stream_config->bps) {
		dev_err(dev, "bps not matching, stream:%s\n", stream->name);
		return -EINVAL;
	}

	stream->type = stream_config->type;
	stream->params.rate = stream_config->frame_rate;
	stream->params.bps = stream_config->bps;

	/* TODO: Update this check during Device-device support */
	if (is_slave)
		stream->params.ch_count += stream_config->ch_count;

	return 0;
}