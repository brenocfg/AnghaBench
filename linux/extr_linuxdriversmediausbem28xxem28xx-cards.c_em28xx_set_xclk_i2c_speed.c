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
typedef  int u8 ;
struct em28xx_board {int xclk; int i2c_speed; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_em2800; } ;
struct em28xx {size_t model; int i2c_speed; TYPE_1__ board; } ;

/* Variables and functions */
 int EM28XX_I2C_CLK_WAIT_ENABLE ; 
 int EM28XX_I2C_FREQ_100_KHZ ; 
 int /*<<< orphan*/  EM28XX_R06_I2C_CLK ; 
 int /*<<< orphan*/  EM28XX_R0F_XCLK ; 
 int EM28XX_XCLK_FREQUENCY_12MHZ ; 
 int EM28XX_XCLK_IR_RC5_MODE ; 
 struct em28xx_board* em28xx_boards ; 
 int /*<<< orphan*/  em28xx_write_reg (struct em28xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static inline void em28xx_set_xclk_i2c_speed(struct em28xx *dev)
{
	const struct em28xx_board *board = &em28xx_boards[dev->model];
	u8 xclk = board->xclk, i2c_speed = board->i2c_speed;

	/*
	 * Those are the default values for the majority of boards
	 * Use those values if not specified otherwise at boards entry
	 */
	if (!xclk)
		xclk = EM28XX_XCLK_IR_RC5_MODE |
		       EM28XX_XCLK_FREQUENCY_12MHZ;

	em28xx_write_reg(dev, EM28XX_R0F_XCLK, xclk);

	if (!i2c_speed)
		i2c_speed = EM28XX_I2C_CLK_WAIT_ENABLE |
			    EM28XX_I2C_FREQ_100_KHZ;

	dev->i2c_speed = i2c_speed & 0x03;

	if (!dev->board.is_em2800)
		em28xx_write_reg(dev, EM28XX_R06_I2C_CLK, i2c_speed);
	msleep(50);
}