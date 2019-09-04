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
struct firmware {int /*<<< orphan*/ * data; } ;
struct device {int dummy; } ;
struct cyapa {TYPE_1__* client; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 size_t CYAPA_FW_BLOCK_SIZE ; 
 size_t CYAPA_FW_DATA_BLOCK_COUNT ; 
 int /*<<< orphan*/  CYAPA_FW_DATA_BLOCK_START ; 
 size_t CYAPA_FW_HDR_BLOCK_COUNT ; 
 int /*<<< orphan*/  CYAPA_FW_HDR_BLOCK_START ; 
 int cyapa_gen3_write_blocks (struct cyapa*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 

__attribute__((used)) static int cyapa_gen3_do_fw_update(struct cyapa *cyapa,
		const struct firmware *fw)
{
	struct device *dev = &cyapa->client->dev;
	int error;

	/* First write data, starting at byte 128 of fw->data */
	error = cyapa_gen3_write_blocks(cyapa,
		CYAPA_FW_DATA_BLOCK_START, CYAPA_FW_DATA_BLOCK_COUNT,
		&fw->data[CYAPA_FW_HDR_BLOCK_COUNT * CYAPA_FW_BLOCK_SIZE]);
	if (error) {
		dev_err(dev, "FW update aborted, write image: %d\n", error);
		return error;
	}

	/* Then write checksum */
	error = cyapa_gen3_write_blocks(cyapa,
		CYAPA_FW_HDR_BLOCK_START, CYAPA_FW_HDR_BLOCK_COUNT,
		&fw->data[0]);
	if (error) {
		dev_err(dev, "FW update aborted, write checksum: %d\n", error);
		return error;
	}

	return 0;
}