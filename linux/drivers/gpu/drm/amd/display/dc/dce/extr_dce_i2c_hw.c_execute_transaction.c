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
struct dce_i2c_hw {scalar_t__ buffer_used_bytes; scalar_t__ transaction_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_I2C_CONTROL ; 
 int /*<<< orphan*/  DC_I2C_DDC1_CLK_DRIVE_EN ; 
 int /*<<< orphan*/  DC_I2C_DDC1_DATA_DRIVE_EN ; 
 int /*<<< orphan*/  DC_I2C_DDC1_DATA_DRIVE_SEL ; 
 int /*<<< orphan*/  DC_I2C_DDC1_INTRA_BYTE_DELAY ; 
 int /*<<< orphan*/  DC_I2C_DDC1_INTRA_TRANSACTION_DELAY ; 
 int /*<<< orphan*/  DC_I2C_DDC1_SETUP ; 
 int /*<<< orphan*/  DC_I2C_GO ; 
 int /*<<< orphan*/  DC_I2C_SEND_RESET ; 
 int /*<<< orphan*/  DC_I2C_SOFT_RESET ; 
 int /*<<< orphan*/  DC_I2C_SW_STATUS_RESET ; 
 int /*<<< orphan*/  DC_I2C_TRANSACTION_COUNT ; 
 int /*<<< orphan*/  FN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  REG_UPDATE_N (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP ; 

__attribute__((used)) static void execute_transaction(
	struct dce_i2c_hw *dce_i2c_hw)
{
	REG_UPDATE_N(SETUP, 5,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_DATA_DRIVE_EN), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_CLK_DRIVE_EN), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_DATA_DRIVE_SEL), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_INTRA_TRANSACTION_DELAY), 0,
		     FN(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_INTRA_BYTE_DELAY), 0);


	REG_UPDATE_5(DC_I2C_CONTROL,
		     DC_I2C_SOFT_RESET, 0,
		     DC_I2C_SW_STATUS_RESET, 0,
		     DC_I2C_SEND_RESET, 0,
		     DC_I2C_GO, 0,
		     DC_I2C_TRANSACTION_COUNT, dce_i2c_hw->transaction_count - 1);

	/* start I2C transfer */
	REG_UPDATE(DC_I2C_CONTROL, DC_I2C_GO, 1);

	/* all transactions were executed and HW buffer became empty
	 * (even though it actually happens when status becomes DONE)
	 */
	dce_i2c_hw->transaction_count = 0;
	dce_i2c_hw->buffer_used_bytes = 0;
}