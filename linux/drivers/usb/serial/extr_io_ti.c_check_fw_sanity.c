#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct firmware {scalar_t__* data; int size; } ;
struct edgeport_serial {TYPE_2__* serial; } ;
struct edgeport_fw_hdr {scalar_t__ checksum; int /*<<< orphan*/  length; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* interface; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_fw_sanity(struct edgeport_serial *serial,
		const struct firmware *fw)
{
	u16 length_total;
	u8 checksum = 0;
	int pos;
	struct device *dev = &serial->serial->interface->dev;
	struct edgeport_fw_hdr *fw_hdr = (struct edgeport_fw_hdr *)fw->data;

	if (fw->size < sizeof(struct edgeport_fw_hdr)) {
		dev_err(dev, "incomplete fw header\n");
		return -EINVAL;
	}

	length_total = le16_to_cpu(fw_hdr->length) +
			sizeof(struct edgeport_fw_hdr);

	if (fw->size != length_total) {
		dev_err(dev, "bad fw size (expected: %u, got: %zu)\n",
				length_total, fw->size);
		return -EINVAL;
	}

	for (pos = sizeof(struct edgeport_fw_hdr); pos < fw->size; ++pos)
		checksum += fw->data[pos];

	if (checksum != fw_hdr->checksum) {
		dev_err(dev, "bad fw checksum (expected: 0x%x, got: 0x%x)\n",
				fw_hdr->checksum, checksum);
		return -EINVAL;
	}

	return 0;
}