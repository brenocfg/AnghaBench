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
typedef  int u16 ;
struct firmware {int* data; int /*<<< orphan*/  size; } ;
struct device {int dummy; } ;
struct cyapa {TYPE_1__* client; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int CYAPA_FW_DATA_SIZE ; 
 int CYAPA_FW_HDR_SIZE ; 
 int /*<<< orphan*/  CYAPA_FW_SIZE ; 
 int EINVAL ; 
 int cyapa_gen3_csum (int*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int,...) ; 

__attribute__((used)) static int cyapa_gen3_check_fw(struct cyapa *cyapa, const struct firmware *fw)
{
	struct device *dev = &cyapa->client->dev;
	u16 csum;
	u16 csum_expected;

	/* Firmware must match exact 30848 bytes = 482 64-byte blocks. */
	if (fw->size != CYAPA_FW_SIZE) {
		dev_err(dev, "invalid firmware size = %zu, expected %u.\n",
			fw->size, CYAPA_FW_SIZE);
		return -EINVAL;
	}

	/* Verify header block */
	csum_expected = (fw->data[0] << 8) | fw->data[1];
	csum = cyapa_gen3_csum(&fw->data[2], CYAPA_FW_HDR_SIZE - 2);
	if (csum != csum_expected) {
		dev_err(dev, "%s %04x, expected: %04x\n",
			"invalid firmware header checksum = ",
			csum, csum_expected);
		return -EINVAL;
	}

	/* Verify firmware image */
	csum_expected = (fw->data[CYAPA_FW_HDR_SIZE - 2] << 8) |
			 fw->data[CYAPA_FW_HDR_SIZE - 1];
	csum = cyapa_gen3_csum(&fw->data[CYAPA_FW_HDR_SIZE],
			CYAPA_FW_DATA_SIZE);
	if (csum != csum_expected) {
		dev_err(dev, "%s %04x, expected: %04x\n",
			"invalid firmware header checksum = ",
			csum, csum_expected);
		return -EINVAL;
	}
	return 0;
}