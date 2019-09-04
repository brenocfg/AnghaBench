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
struct tda18250_dev {int warm; size_t xtal_freq; int /*<<< orphan*/  regmap; scalar_t__ loopthrough; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct i2c_client* tuner_priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const**) ; 
 int const R0A_IRQ3 ; 
#define  R0C_AGC11 166 
#define  R0D_AGC12 165 
#define  R0E_AGC13 164 
#define  R0F_AGC14 163 
#define  R10_LT1 162 
#define  R11_LT2 161 
#define  R12_AGC21 160 
#define  R13_AGC22 159 
#define  R18_AGC32 158 
#define  R19_AGC33 157 
#define  R1A_AGCK 156 
#define  R1E_WI_FI 155 
#define  R1F_RF_BPF 154 
#define  R20_IR_MIX 153 
#define  R21_IF_AGC 152 
 int const R2A_MSM1 ; 
 int const R2B_MSM2 ; 
#define  R2C_PS1 151 
#define  R2D_PS2 150 
#define  R2E_PS3 149 
#define  R30_RSSI2 148 
#define  R31_IRQ_CTRL 147 
#define  R39_SD5 146 
#define  R3B_REGU 145 
#define  R3C_RCCAL1 144 
#define  R3F_IRCAL2 143 
#define  R40_IRCAL3 142 
#define  R41_IRCAL4 141 
#define  R43_PD1 140 
#define  R44_PD2 139 
#define  R46_CPUMP 138 
#define  R47_LNAPOL 137 
#define  R4B_XTALOSC1 136 
 int /*<<< orphan*/  R4D_XTALFLX1 ; 
#define  R59_AGC2_UP2 135 
#define  R5B_AGC_AUTO 134 
#define  R5C_AGC_DEBUG 133 
 int TDA18250_IRQ_CAL ; 
 int TDA18250_IRQ_HW_INIT ; 
 int /*<<< orphan*/  TDA18250_POWER_NORMAL ; 
#define  TDA18250_XTAL_FREQ_16MHZ 132 
#define  TDA18250_XTAL_FREQ_24MHZ 131 
#define  TDA18250_XTAL_FREQ_25MHZ 130 
#define  TDA18250_XTAL_FREQ_27MHZ 129 
#define  TDA18250_XTAL_FREQ_30MHZ 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct tda18250_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int const,int const) ; 
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int,int) ; 
 int tda18250_power_control (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int tda18250_wait_for_irq (struct dvb_frontend*,int,int,int) ; 

__attribute__((used)) static int tda18250_init(struct dvb_frontend *fe)
{
	struct i2c_client *client = fe->tuner_priv;
	struct tda18250_dev *dev = i2c_get_clientdata(client);
	int ret, i;

	/* default values for various regs */
	static const u8 init_regs[][2] = {
		{ R0C_AGC11, 0xc7 },
		{ R0D_AGC12, 0x5d },
		{ R0E_AGC13, 0x40 },
		{ R0F_AGC14, 0x0e },
		{ R10_LT1, 0x47 },
		{ R11_LT2, 0x4e },
		{ R12_AGC21, 0x26 },
		{ R13_AGC22, 0x60 },
		{ R18_AGC32, 0x37 },
		{ R19_AGC33, 0x09 },
		{ R1A_AGCK, 0x00 },
		{ R1E_WI_FI, 0x29 },
		{ R1F_RF_BPF, 0x06 },
		{ R20_IR_MIX, 0xc6 },
		{ R21_IF_AGC, 0x00 },
		{ R2C_PS1, 0x75 },
		{ R2D_PS2, 0x06 },
		{ R2E_PS3, 0x07 },
		{ R30_RSSI2, 0x0e },
		{ R31_IRQ_CTRL, 0x00 },
		{ R39_SD5, 0x00 },
		{ R3B_REGU, 0x55 },
		{ R3C_RCCAL1, 0xa7 },
		{ R3F_IRCAL2, 0x85 },
		{ R40_IRCAL3, 0x87 },
		{ R41_IRCAL4, 0xc0 },
		{ R43_PD1, 0x40 },
		{ R44_PD2, 0xc0 },
		{ R46_CPUMP, 0x0c },
		{ R47_LNAPOL, 0x64 },
		{ R4B_XTALOSC1, 0x30 },
		{ R59_AGC2_UP2, 0x05 },
		{ R5B_AGC_AUTO, 0x07 },
		{ R5C_AGC_DEBUG, 0x00 },
	};

	/* crystal related regs depend on frequency */
	static const u8 xtal_regs[][5] = {
					/* reg:   4d    4e    4f    50    51 */
		[TDA18250_XTAL_FREQ_16MHZ]  = { 0x3e, 0x80, 0x50, 0x00, 0x20 },
		[TDA18250_XTAL_FREQ_24MHZ]  = { 0x5d, 0xc0, 0xec, 0x00, 0x18 },
		[TDA18250_XTAL_FREQ_25MHZ]  = { 0x61, 0xa8, 0xec, 0x80, 0x19 },
		[TDA18250_XTAL_FREQ_27MHZ]  = { 0x69, 0x78, 0x8d, 0x80, 0x1b },
		[TDA18250_XTAL_FREQ_30MHZ]  = { 0x75, 0x30, 0x8f, 0x00, 0x1e },
	};

	dev_dbg(&client->dev, "\n");

	ret = tda18250_power_control(fe, TDA18250_POWER_NORMAL);
	if (ret)
		goto err;

	msleep(20);

	if (dev->warm)
		goto warm;

	/* set initial register values */
	for (i = 0; i < ARRAY_SIZE(init_regs); i++) {
		ret = regmap_write(dev->regmap, init_regs[i][0],
				init_regs[i][1]);
		if (ret)
			goto err;
	}

	/* set xtal related regs */
	ret = regmap_bulk_write(dev->regmap, R4D_XTALFLX1,
			xtal_regs[dev->xtal_freq], 5);
	if (ret)
		goto err;

	ret = regmap_write_bits(dev->regmap, R10_LT1, 0x80,
			dev->loopthrough ? 0x00 : 0x80);
	if (ret)
		goto err;

	/* clear IRQ */
	ret = regmap_write(dev->regmap, R0A_IRQ3, TDA18250_IRQ_HW_INIT);
	if (ret)
		goto err;

	/* start HW init */
	ret = regmap_write(dev->regmap, R2A_MSM1, 0x70);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, R2B_MSM2, 0x01);
	if (ret)
		goto err;

	ret = tda18250_wait_for_irq(fe, 500, 10, TDA18250_IRQ_HW_INIT);
	if (ret)
		goto err;

	/* tuner calibration */
	ret = regmap_write(dev->regmap, R2A_MSM1, 0x02);
	if (ret)
		goto err;

	ret = regmap_write(dev->regmap, R2B_MSM2, 0x01);
	if (ret)
		goto err;

	ret = tda18250_wait_for_irq(fe, 500, 10, TDA18250_IRQ_CAL);
	if (ret)
		goto err;

	dev->warm = true;

warm:
	/* power up LNA */
	ret = regmap_write_bits(dev->regmap, R0C_AGC11, 0x80, 0x00);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d", ret);
	return ret;
}