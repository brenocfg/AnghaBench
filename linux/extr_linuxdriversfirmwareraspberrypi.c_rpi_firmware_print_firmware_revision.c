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
typedef  int /*<<< orphan*/  variant ;
typedef  size_t u32 ;
struct tm {int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; scalar_t__ tm_mon; scalar_t__ tm_year; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct rpi_firmware {TYPE_1__ cl; } ;
typedef  int /*<<< orphan*/  packet ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const* const*) ; 
 int /*<<< orphan*/  RPI_FIRMWARE_GET_FIRMWARE_REVISION ; 
 int /*<<< orphan*/  RPI_FIRMWARE_GET_FIRMWARE_VARIANT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int rpi_firmware_property (struct rpi_firmware*,int /*<<< orphan*/ ,size_t*,int) ; 
 int /*<<< orphan*/  time64_to_tm (size_t,int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static void
rpi_firmware_print_firmware_revision(struct rpi_firmware *fw)
{
	static const char * const variant_strs[] = {
		"unknown",
		"start",
		"start_x",
		"start_db",
		"start_cd",
	};
	const char *variant_str = "cmd unsupported";
	u32 packet;
	u32 variant;
	struct tm tm;
	int ret = rpi_firmware_property(fw,
					RPI_FIRMWARE_GET_FIRMWARE_REVISION,
					&packet, sizeof(packet));

	if (ret)
		return;

	ret = rpi_firmware_property(fw, RPI_FIRMWARE_GET_FIRMWARE_VARIANT,
				    &variant, sizeof(variant));

	if (!ret) {
		if (variant >= ARRAY_SIZE(variant_strs))
			variant = 0;
		variant_str = variant_strs[variant];
	}

	time64_to_tm(packet, 0, &tm);

	dev_info(fw->cl.dev,
		 "Attached to firmware from %04ld-%02d-%02d %02d:%02d, variant %s\n",
		 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
		 tm.tm_min, variant_str);
}