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
struct solo_dev {int tw28_cnt; int nr_chans; int tw2865; int tw2864; int tw2815; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SOLO_I2C_TW ; 
 int /*<<< orphan*/  TW_CHIP_OFFSET_ADDR (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  saa712x_setup (struct solo_dev*) ; 
 int solo_i2c_readbyte (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw2815_setup (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw2864_setup (struct solo_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw2865_setup (struct solo_dev*,int /*<<< orphan*/ ) ; 

int solo_tw28_init(struct solo_dev *solo_dev)
{
	int i;
	u8 value;

	solo_dev->tw28_cnt = 0;

	/* Detect techwell chip type(s) */
	for (i = 0; i < solo_dev->nr_chans / 4; i++) {
		value = solo_i2c_readbyte(solo_dev, SOLO_I2C_TW,
					  TW_CHIP_OFFSET_ADDR(i), 0xFF);

		switch (value >> 3) {
		case 0x18:
			solo_dev->tw2865 |= 1 << i;
			solo_dev->tw28_cnt++;
			break;
		case 0x0c:
		case 0x0d:
			solo_dev->tw2864 |= 1 << i;
			solo_dev->tw28_cnt++;
			break;
		default:
			value = solo_i2c_readbyte(solo_dev, SOLO_I2C_TW,
						  TW_CHIP_OFFSET_ADDR(i),
						  0x59);
			if ((value >> 3) == 0x04) {
				solo_dev->tw2815 |= 1 << i;
				solo_dev->tw28_cnt++;
			}
		}
	}

	if (solo_dev->tw28_cnt != (solo_dev->nr_chans >> 2)) {
		dev_err(&solo_dev->pdev->dev,
			"Could not initialize any techwell chips\n");
		return -EINVAL;
	}

	saa712x_setup(solo_dev);

	for (i = 0; i < solo_dev->tw28_cnt; i++) {
		if ((solo_dev->tw2865 & (1 << i)))
			tw2865_setup(solo_dev, TW_CHIP_OFFSET_ADDR(i));
		else if ((solo_dev->tw2864 & (1 << i)))
			tw2864_setup(solo_dev, TW_CHIP_OFFSET_ADDR(i));
		else
			tw2815_setup(solo_dev, TW_CHIP_OFFSET_ADDR(i));
	}

	return 0;
}