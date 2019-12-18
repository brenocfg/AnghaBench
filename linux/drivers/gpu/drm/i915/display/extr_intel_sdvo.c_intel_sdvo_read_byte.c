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
typedef  int /*<<< orphan*/  u8 ;
struct intel_sdvo {int /*<<< orphan*/  i2c; int /*<<< orphan*/  slave_addr; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static bool intel_sdvo_read_byte(struct intel_sdvo *intel_sdvo, u8 addr, u8 *ch)
{
	struct i2c_msg msgs[] = {
		{
			.addr = intel_sdvo->slave_addr,
			.flags = 0,
			.len = 1,
			.buf = &addr,
		},
		{
			.addr = intel_sdvo->slave_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = ch,
		}
	};
	int ret;

	if ((ret = i2c_transfer(intel_sdvo->i2c, msgs, 2)) == 2)
		return true;

	DRM_DEBUG_KMS("i2c transfer returned %d\n", ret);
	return false;
}