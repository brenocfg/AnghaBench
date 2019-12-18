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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct telemetry_unit_config {int ssram_evts_used; scalar_t__ regmap; } ;
struct telem_ssram_region {scalar_t__ timestamp; scalar_t__* events; scalar_t__ start_time; } ;
typedef  enum telemetry_unit { ____Placeholder_telemetry_unit } telemetry_unit ;

/* Variables and functions */
 int BYTES_PER_LONG ; 
 int EBUSY ; 
 scalar_t__ TELEM_SSRAM_EVTLOG_OFFSET ; 
 int /*<<< orphan*/  TELEM_SSRAM_READ_TIMEOUT ; 
 scalar_t__ TELEM_SSRAM_STARTTIME_OFFSET ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ readq (scalar_t__) ; 
 int telem_get_unitconfig (int,struct telemetry_unit_config**) ; 

__attribute__((used)) static int telem_evtlog_read(enum telemetry_unit telem_unit,
			     struct telem_ssram_region *ssram_region, u8 len)
{
	struct telemetry_unit_config *unit_config;
	u64 timestamp_prev, timestamp_next;
	int ret, index, timeout = 0;

	ret = telem_get_unitconfig(telem_unit, &unit_config);
	if (ret < 0)
		return ret;

	if (len > unit_config->ssram_evts_used)
		len = unit_config->ssram_evts_used;

	do {
		timestamp_prev = readq(unit_config->regmap);
		if (!timestamp_prev) {
			pr_err("Ssram under update. Please Try Later\n");
			return -EBUSY;
		}

		ssram_region->start_time = readq(unit_config->regmap +
						 TELEM_SSRAM_STARTTIME_OFFSET);

		for (index = 0; index < len; index++) {
			ssram_region->events[index] =
			readq(unit_config->regmap + TELEM_SSRAM_EVTLOG_OFFSET +
			      BYTES_PER_LONG*index);
		}

		timestamp_next = readq(unit_config->regmap);
		if (!timestamp_next) {
			pr_err("Ssram under update. Please Try Later\n");
			return -EBUSY;
		}

		if (timeout++ > TELEM_SSRAM_READ_TIMEOUT) {
			pr_err("Timeout while reading Events\n");
			return -EBUSY;
		}

	} while (timestamp_prev != timestamp_next);

	ssram_region->timestamp = timestamp_next;

	return len;
}