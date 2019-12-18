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
typedef  int /*<<< orphan*/  u8 ;
struct occ_sensor {int num_sensors; int /*<<< orphan*/ * data; int /*<<< orphan*/  version; } ;
struct occ_sensors {struct occ_sensor extended; struct occ_sensor caps; struct occ_sensor power; struct occ_sensor freq; struct occ_sensor temp; } ;
struct TYPE_2__ {int num_sensors; int sensor_length; int /*<<< orphan*/  sensor_format; int /*<<< orphan*/  eye_catcher; } ;
struct occ_sensor_data_block {int /*<<< orphan*/  data; TYPE_1__ header; } ;
struct occ_response {int /*<<< orphan*/ * data; } ;
struct occ_poll_response_header {unsigned int num_sensor_data_blocks; int /*<<< orphan*/  occ_code_level; } ;
struct occ_poll_response {struct occ_sensor_data_block block; struct occ_poll_response_header header; } ;
struct occ {int /*<<< orphan*/  bus_dev; struct occ_response resp; struct occ_sensors sensors; } ;

/* Variables and functions */
 unsigned int OCC_RESP_DATA_BYTES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int,unsigned int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void occ_parse_poll_response(struct occ *occ)
{
	unsigned int i, old_offset, offset = 0, size = 0;
	struct occ_sensor *sensor;
	struct occ_sensors *sensors = &occ->sensors;
	struct occ_response *resp = &occ->resp;
	struct occ_poll_response *poll =
		(struct occ_poll_response *)&resp->data[0];
	struct occ_poll_response_header *header = &poll->header;
	struct occ_sensor_data_block *block = &poll->block;

	dev_info(occ->bus_dev, "OCC found, code level: %.16s\n",
		 header->occ_code_level);

	for (i = 0; i < header->num_sensor_data_blocks; ++i) {
		block = (struct occ_sensor_data_block *)((u8 *)block + offset);
		old_offset = offset;
		offset = (block->header.num_sensors *
			  block->header.sensor_length) + sizeof(block->header);
		size += offset;

		/* validate all the length/size fields */
		if ((size + sizeof(*header)) >= OCC_RESP_DATA_BYTES) {
			dev_warn(occ->bus_dev, "exceeded response buffer\n");
			return;
		}

		dev_dbg(occ->bus_dev, " %04x..%04x: %.4s (%d sensors)\n",
			old_offset, offset - 1, block->header.eye_catcher,
			block->header.num_sensors);

		/* match sensor block type */
		if (strncmp(block->header.eye_catcher, "TEMP", 4) == 0)
			sensor = &sensors->temp;
		else if (strncmp(block->header.eye_catcher, "FREQ", 4) == 0)
			sensor = &sensors->freq;
		else if (strncmp(block->header.eye_catcher, "POWR", 4) == 0)
			sensor = &sensors->power;
		else if (strncmp(block->header.eye_catcher, "CAPS", 4) == 0)
			sensor = &sensors->caps;
		else if (strncmp(block->header.eye_catcher, "EXTN", 4) == 0)
			sensor = &sensors->extended;
		else {
			dev_warn(occ->bus_dev, "sensor not supported %.4s\n",
				 block->header.eye_catcher);
			continue;
		}

		sensor->num_sensors = block->header.num_sensors;
		sensor->version = block->header.sensor_format;
		sensor->data = &block->data;
	}

	dev_dbg(occ->bus_dev, "Max resp size: %u+%zd=%zd\n", size,
		sizeof(*header), size + sizeof(*header));
}