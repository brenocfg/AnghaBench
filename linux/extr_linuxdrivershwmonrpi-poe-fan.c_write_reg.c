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
typedef  int /*<<< orphan*/  u32 ;
struct rpi_firmware {int dummy; } ;
struct fw_tag_data_s {scalar_t__ ret; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  fw_tag_data ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  RPI_FIRMWARE_SET_POE_HAT_VAL ; 
 int rpi_firmware_property (struct rpi_firmware*,int /*<<< orphan*/ ,struct fw_tag_data_s*,int) ; 

__attribute__((used)) static int write_reg(struct rpi_firmware *fw, u32 reg, u32 *val){
	struct fw_tag_data_s fw_tag_data = {
		.reg = reg,
		.val = *val
	};
	int ret;
	ret = rpi_firmware_property(fw, RPI_FIRMWARE_SET_POE_HAT_VAL,
				    &fw_tag_data, sizeof(fw_tag_data));
	if (ret) {
		return ret;
	} else if (fw_tag_data.ret) {
		return -EIO;
	}
	return 0;
}