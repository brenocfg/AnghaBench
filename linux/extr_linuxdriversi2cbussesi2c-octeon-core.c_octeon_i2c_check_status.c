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
struct octeon_i2c {int /*<<< orphan*/  dev; scalar_t__ twsi_base; scalar_t__ hlc_enabled; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
#define  STAT_AD2W_ACK 154 
#define  STAT_AD2W_NAK 153 
#define  STAT_BUS_ERROR 152 
#define  STAT_GENDATA_ACK 151 
#define  STAT_GENDATA_NAK 150 
#define  STAT_IDLE 149 
#define  STAT_LOST_ARB_38 148 
#define  STAT_LOST_ARB_68 147 
#define  STAT_LOST_ARB_78 146 
#define  STAT_LOST_ARB_B0 145 
#define  STAT_RXADDR_ACK 144 
#define  STAT_RXADDR_NAK 143 
#define  STAT_RXDATA_ACK 142 
#define  STAT_RXDATA_NAK 141 
#define  STAT_SLAVE_60 140 
#define  STAT_SLAVE_70 139 
#define  STAT_SLAVE_80 138 
#define  STAT_SLAVE_88 137 
#define  STAT_SLAVE_A0 136 
#define  STAT_SLAVE_A8 135 
#define  STAT_SLAVE_ACK 134 
#define  STAT_SLAVE_LOST 133 
#define  STAT_SLAVE_NAK 132 
#define  STAT_TXADDR_ACK 131 
#define  STAT_TXADDR_NAK 130 
#define  STAT_TXDATA_ACK 129 
#define  STAT_TXDATA_NAK 128 
 scalar_t__ SW_TWSI (struct octeon_i2c*) ; 
 int __raw_readq (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int octeon_i2c_stat_read (struct octeon_i2c*) ; 

__attribute__((used)) static int octeon_i2c_check_status(struct octeon_i2c *i2c, int final_read)
{
	u8 stat;

	/*
	 * This is ugly... in HLC mode the status is not in the status register
	 * but in the lower 8 bits of SW_TWSI.
	 */
	if (i2c->hlc_enabled)
		stat = __raw_readq(i2c->twsi_base + SW_TWSI(i2c));
	else
		stat = octeon_i2c_stat_read(i2c);

	switch (stat) {
	/* Everything is fine */
	case STAT_IDLE:
	case STAT_AD2W_ACK:
	case STAT_RXADDR_ACK:
	case STAT_TXADDR_ACK:
	case STAT_TXDATA_ACK:
		return 0;

	/* ACK allowed on pre-terminal bytes only */
	case STAT_RXDATA_ACK:
		if (!final_read)
			return 0;
		return -EIO;

	/* NAK allowed on terminal byte only */
	case STAT_RXDATA_NAK:
		if (final_read)
			return 0;
		return -EIO;

	/* Arbitration lost */
	case STAT_LOST_ARB_38:
	case STAT_LOST_ARB_68:
	case STAT_LOST_ARB_78:
	case STAT_LOST_ARB_B0:
		return -EAGAIN;

	/* Being addressed as slave, should back off & listen */
	case STAT_SLAVE_60:
	case STAT_SLAVE_70:
	case STAT_GENDATA_ACK:
	case STAT_GENDATA_NAK:
		return -EOPNOTSUPP;

	/* Core busy as slave */
	case STAT_SLAVE_80:
	case STAT_SLAVE_88:
	case STAT_SLAVE_A0:
	case STAT_SLAVE_A8:
	case STAT_SLAVE_LOST:
	case STAT_SLAVE_NAK:
	case STAT_SLAVE_ACK:
		return -EOPNOTSUPP;

	case STAT_TXDATA_NAK:
	case STAT_BUS_ERROR:
		return -EIO;
	case STAT_TXADDR_NAK:
	case STAT_RXADDR_NAK:
	case STAT_AD2W_NAK:
		return -ENXIO;
	default:
		dev_err(i2c->dev, "unhandled state: %d\n", stat);
		return -EIO;
	}
}