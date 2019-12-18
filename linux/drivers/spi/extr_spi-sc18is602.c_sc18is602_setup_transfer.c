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
typedef  int u8 ;
typedef  int u32 ;
struct sc18is602 {int freq; int speed; int ctrl; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int SC18IS602_MODE_CLOCK_DIV_128 ; 
 int SC18IS602_MODE_CLOCK_DIV_16 ; 
 int SC18IS602_MODE_CLOCK_DIV_4 ; 
 int SC18IS602_MODE_CLOCK_DIV_64 ; 
 int SC18IS602_MODE_CPHA ; 
 int SC18IS602_MODE_CPOL ; 
 int SC18IS602_MODE_LSB_FIRST ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
 int SPI_LSB_FIRST ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sc18is602_setup_transfer(struct sc18is602 *hw, u32 hz, u8 mode)
{
	u8 ctrl = 0;
	int ret;

	if (mode & SPI_CPHA)
		ctrl |= SC18IS602_MODE_CPHA;
	if (mode & SPI_CPOL)
		ctrl |= SC18IS602_MODE_CPOL;
	if (mode & SPI_LSB_FIRST)
		ctrl |= SC18IS602_MODE_LSB_FIRST;

	/* Find the closest clock speed */
	if (hz >= hw->freq / 4) {
		ctrl |= SC18IS602_MODE_CLOCK_DIV_4;
		hw->speed = hw->freq / 4;
	} else if (hz >= hw->freq / 16) {
		ctrl |= SC18IS602_MODE_CLOCK_DIV_16;
		hw->speed = hw->freq / 16;
	} else if (hz >= hw->freq / 64) {
		ctrl |= SC18IS602_MODE_CLOCK_DIV_64;
		hw->speed = hw->freq / 64;
	} else {
		ctrl |= SC18IS602_MODE_CLOCK_DIV_128;
		hw->speed = hw->freq / 128;
	}

	/*
	 * Don't do anything if the control value did not change. The initial
	 * value of 0xff for hw->ctrl ensures that the correct mode will be set
	 * with the first call to this function.
	 */
	if (ctrl == hw->ctrl)
		return 0;

	ret = i2c_smbus_write_byte_data(hw->client, 0xf0, ctrl);
	if (ret < 0)
		return ret;

	hw->ctrl = ctrl;

	return 0;
}