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

/* Variables and functions */
 int EINVAL ; 
 int _sdw_deprepare_stream (struct sdw_stream_runtime*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sdw_acquire_bus_lock (struct sdw_stream_runtime*) ; 
 int /*<<< orphan*/  sdw_release_bus_lock (struct sdw_stream_runtime*) ; 

int sdw_deprepare_stream(struct sdw_stream_runtime *stream)
{
	int ret;

	if (!stream) {
		pr_err("SoundWire: Handle not found for stream\n");
		return -EINVAL;
	}

	sdw_acquire_bus_lock(stream);
	ret = _sdw_deprepare_stream(stream);
	if (ret < 0)
		pr_err("De-prepare for stream:%d failed: %d\n", ret, ret);

	sdw_release_bus_lock(stream);
	return ret;
}