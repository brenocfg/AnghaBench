#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct falcon_fw_os_header_v1 {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data_offset; int /*<<< orphan*/  code_size; int /*<<< orphan*/  code_offset; } ;
struct falcon_fw_bin_header_v1 {scalar_t__ magic; int version; scalar_t__ size; int os_header_offset; int /*<<< orphan*/  os_data_offset; int /*<<< orphan*/  os_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  size; } ;
struct TYPE_8__ {scalar_t__ size; TYPE_3__ data; TYPE_2__ code; TYPE_1__ bin_data; struct falcon_fw_os_header_v1* vaddr; } ;
struct falcon {TYPE_4__ firmware; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCI_VENDOR_ID_NVIDIA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int falcon_parse_firmware_image(struct falcon *falcon)
{
	struct falcon_fw_bin_header_v1 *bin = (void *)falcon->firmware.vaddr;
	struct falcon_fw_os_header_v1 *os;

	/* endian problems would show up right here */
	if (bin->magic != PCI_VENDOR_ID_NVIDIA) {
		dev_err(falcon->dev, "incorrect firmware magic\n");
		return -EINVAL;
	}

	/* currently only version 1 is supported */
	if (bin->version != 1) {
		dev_err(falcon->dev, "unsupported firmware version\n");
		return -EINVAL;
	}

	/* check that the firmware size is consistent */
	if (bin->size > falcon->firmware.size) {
		dev_err(falcon->dev, "firmware image size inconsistency\n");
		return -EINVAL;
	}

	os = falcon->firmware.vaddr + bin->os_header_offset;

	falcon->firmware.bin_data.size = bin->os_size;
	falcon->firmware.bin_data.offset = bin->os_data_offset;
	falcon->firmware.code.offset = os->code_offset;
	falcon->firmware.code.size = os->code_size;
	falcon->firmware.data.offset = os->data_offset;
	falcon->firmware.data.size = os->data_size;

	return 0;
}