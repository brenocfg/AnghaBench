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
struct TYPE_2__ {int /*<<< orphan*/  twl_idcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IDCODE_7_0 ; 
 int /*<<< orphan*/  REG_UNLOCK_TEST_REG ; 
 int /*<<< orphan*/  TWL4030_MODULE_INTBR ; 
 int TWL_EEPROM_R_UNLOCK ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int twl_i2c_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* twl_priv ; 

__attribute__((used)) static int twl_read_idcode_register(void)
{
	int err;

	err = twl_i2c_write_u8(TWL4030_MODULE_INTBR, TWL_EEPROM_R_UNLOCK,
						REG_UNLOCK_TEST_REG);
	if (err) {
		pr_err("TWL4030 Unable to unlock IDCODE registers -%d\n", err);
		goto fail;
	}

	err = twl_i2c_read(TWL4030_MODULE_INTBR, (u8 *)(&twl_priv->twl_idcode),
						REG_IDCODE_7_0, 4);
	if (err) {
		pr_err("TWL4030: unable to read IDCODE -%d\n", err);
		goto fail;
	}

	err = twl_i2c_write_u8(TWL4030_MODULE_INTBR, 0x0, REG_UNLOCK_TEST_REG);
	if (err)
		pr_err("TWL4030 Unable to relock IDCODE registers -%d\n", err);
fail:
	return err;
}