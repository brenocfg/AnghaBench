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
struct encx24j600_context {int bank; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int ADDR_MASK ; 
 int BANK_MASK ; 
 int BANK_SHIFT ; 
#define  EGPDATA 136 
#define  EGPRDPT 135 
#define  EGPWRPT 134 
 int EINVAL ; 
#define  ERXDATA 133 
#define  ERXRDPT 132 
#define  ERXWRPT 131 
#define  EUDADATA 130 
#define  EUDARDPT 129 
#define  EUDAWRPT 128 
 int RCRCODE ; 
 int RCRU ; 
 int RGPRDPT ; 
 int RGPWRPT ; 
 int RRXRDPT ; 
 int RRXWRPT ; 
 int RUDARDPT ; 
 int RUDAWRPT ; 
 int encx24j600_switch_bank (struct encx24j600_context*,int) ; 
 int spi_write_then_read (int /*<<< orphan*/ ,int*,int,int*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int regmap_encx24j600_sfr_read(void *context, u8 reg, u8 *val,
				      size_t len)
{
	struct encx24j600_context *ctx = context;
	u8 banked_reg = reg & ADDR_MASK;
	u8 bank = ((reg & BANK_MASK) >> BANK_SHIFT);
	u8 cmd = RCRU;
	int ret = 0;
	int i = 0;
	u8 tx_buf[2];

	if (reg < 0x80) {
		cmd = RCRCODE | banked_reg;
		if ((banked_reg < 0x16) && (ctx->bank != bank))
			ret = encx24j600_switch_bank(ctx, bank);
		if (unlikely(ret))
			return ret;
	} else {
		/* Translate registers that are more effecient using
		 * 3-byte SPI commands
		 */
		switch (reg) {
		case EGPRDPT:
			cmd = RGPRDPT; break;
		case EGPWRPT:
			cmd = RGPWRPT; break;
		case ERXRDPT:
			cmd = RRXRDPT; break;
		case ERXWRPT:
			cmd = RRXWRPT; break;
		case EUDARDPT:
			cmd = RUDARDPT; break;
		case EUDAWRPT:
			cmd = RUDAWRPT; break;
		case EGPDATA:
		case ERXDATA:
		case EUDADATA:
		default:
			return -EINVAL;
		}
	}

	tx_buf[i++] = cmd;
	if (cmd == RCRU)
		tx_buf[i++] = reg;

	ret = spi_write_then_read(ctx->spi, tx_buf, i, val, len);

	return ret;
}