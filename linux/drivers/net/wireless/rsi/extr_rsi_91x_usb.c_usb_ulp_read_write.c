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
typedef  int u32 ;
typedef  int u16 ;
struct rsi_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSI_GSPI_CTRL_REG0 ; 
 int RSI_GSPI_CTRL_REG0_VALUE ; 
 int /*<<< orphan*/  RSI_GSPI_CTRL_REG1 ; 
 int /*<<< orphan*/  RSI_GSPI_DATA_REG0 ; 
 int /*<<< orphan*/  RSI_GSPI_DATA_REG1 ; 
 int RSI_GSPI_TRIG ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rsi_usb_master_reg_write (struct rsi_hw*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int usb_ulp_read_write(struct rsi_hw *adapter, u16 addr, u32 data,
			      u16 len_in_bits)
{
	int ret;

	ret = rsi_usb_master_reg_write
			(adapter, RSI_GSPI_DATA_REG1,
			 ((addr << 6) | ((data >> 16) & 0xffff)), 2);
	if (ret < 0)
		return ret;

	ret = rsi_usb_master_reg_write(adapter, RSI_GSPI_DATA_REG0,
				       (data & 0xffff), 2);
	if (ret < 0)
		return ret;

	/* Initializing GSPI for ULP read/writes */
	rsi_usb_master_reg_write(adapter, RSI_GSPI_CTRL_REG0,
				 RSI_GSPI_CTRL_REG0_VALUE, 2);

	ret = rsi_usb_master_reg_write(adapter, RSI_GSPI_CTRL_REG1,
				       ((len_in_bits - 1) | RSI_GSPI_TRIG), 2);
	if (ret < 0)
		return ret;

	msleep(20);

	return 0;
}