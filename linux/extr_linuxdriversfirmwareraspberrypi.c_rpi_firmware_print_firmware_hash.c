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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct rpi_firmware {TYPE_1__ cl; } ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int /*<<< orphan*/  RPI_FIRMWARE_GET_FIRMWARE_HASH ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rpi_firmware_property (struct rpi_firmware*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
rpi_firmware_print_firmware_hash(struct rpi_firmware *fw)
{
	u32 hash[5];
	int ret = rpi_firmware_property(fw,
					RPI_FIRMWARE_GET_FIRMWARE_HASH,
					hash, sizeof(hash));

	if (ret)
		return;

	dev_info(fw->cl.dev,
		 "Firmware hash is %08x%08x%08x%08x%08x\n",
		 hash[0], hash[1], hash[2], hash[3], hash[4]);
}