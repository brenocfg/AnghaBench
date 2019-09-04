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
struct spi_nor {int (* write_reg ) (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ;int* cmd_buf; } ;
struct flash_info {int dummy; } ;

/* Variables and functions */
 int const JEDEC_MFR (struct flash_info const*) ; 
#define  SNOR_MFR_MACRONIX 130 
#define  SNOR_MFR_MICRON 129 
#define  SNOR_MFR_WINBOND 128 
 int /*<<< orphan*/  SPINOR_OP_BRWR ; 
 int /*<<< orphan*/  SPINOR_OP_EN4B ; 
 int /*<<< orphan*/  SPINOR_OP_EX4B ; 
 int /*<<< orphan*/  SPINOR_OP_WREAR ; 
 int stub1 (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ; 
 int stub2 (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ; 
 int stub3 (struct spi_nor*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  write_disable (struct spi_nor*) ; 
 int /*<<< orphan*/  write_enable (struct spi_nor*) ; 

__attribute__((used)) static inline int set_4byte(struct spi_nor *nor, const struct flash_info *info,
			    int enable)
{
	int status;
	bool need_wren = false;
	u8 cmd;

	switch (JEDEC_MFR(info)) {
	case SNOR_MFR_MICRON:
		/* Some Micron need WREN command; all will accept it */
		need_wren = true;
	case SNOR_MFR_MACRONIX:
	case SNOR_MFR_WINBOND:
		if (need_wren)
			write_enable(nor);

		cmd = enable ? SPINOR_OP_EN4B : SPINOR_OP_EX4B;
		status = nor->write_reg(nor, cmd, NULL, 0);
		if (need_wren)
			write_disable(nor);

		if (!status && !enable &&
		    JEDEC_MFR(info) == SNOR_MFR_WINBOND) {
			/*
			 * On Winbond W25Q256FV, leaving 4byte mode causes
			 * the Extended Address Register to be set to 1, so all
			 * 3-byte-address reads come from the second 16M.
			 * We must clear the register to enable normal behavior.
			 */
			write_enable(nor);
			nor->cmd_buf[0] = 0;
			nor->write_reg(nor, SPINOR_OP_WREAR, nor->cmd_buf, 1);
			write_disable(nor);
		}

		return status;
	default:
		/* Spansion style */
		nor->cmd_buf[0] = enable << 7;
		return nor->write_reg(nor, SPINOR_OP_BRWR, nor->cmd_buf, 1);
	}
}