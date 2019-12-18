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
typedef  int u16 ;
struct TYPE_2__ {int (* write ) (int /*<<< orphan*/ ,scalar_t__,int) ;int /*<<< orphan*/  client; } ;
struct adt7316_chip_info {int config3; int dac_bits; TYPE_1__ bus; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ADT7316_DA_10_BIT_LSB_SHIFT ; 
 int ADT7316_DA_12_BIT_LSB_SHIFT ; 
 scalar_t__ ADT7316_DA_DATA_BASE ; 
 int ADT7316_DA_MSB_DATA_REGS ; 
 int ADT7316_EN_EX_TEMP_PROP_DACB ; 
 int ADT7316_EN_IN_TEMP_PROP_DACA ; 
 size_t EINVAL ; 
 size_t EIO ; 
 size_t EPERM ; 
 int kstrtou16 (char const*,int,int*) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int stub2 (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static ssize_t adt7316_store_DAC(struct adt7316_chip_info *chip,
				 int channel, const char *buf, size_t len)
{
	u8 msb, lsb, lsb_reg, offset;
	u16 data;
	int ret;

	if (channel >= ADT7316_DA_MSB_DATA_REGS ||
	    (channel == 0 &&
	    (chip->config3 & ADT7316_EN_IN_TEMP_PROP_DACA)) ||
	    (channel == 1 &&
	    (chip->config3 & ADT7316_EN_EX_TEMP_PROP_DACB)))
		return -EPERM;

	offset = chip->dac_bits - 8;

	ret = kstrtou16(buf, 10, &data);
	if (ret || data >= (1 << chip->dac_bits))
		return -EINVAL;

	if (chip->dac_bits > 8) {
		lsb = data & ((1 << offset) - 1);
		if (chip->dac_bits == 12)
			lsb_reg = lsb << ADT7316_DA_12_BIT_LSB_SHIFT;
		else
			lsb_reg = lsb << ADT7316_DA_10_BIT_LSB_SHIFT;
		ret = chip->bus.write(chip->bus.client,
			ADT7316_DA_DATA_BASE + channel * 2, lsb_reg);
		if (ret)
			return -EIO;
	}

	msb = data >> offset;
	ret = chip->bus.write(chip->bus.client,
		ADT7316_DA_DATA_BASE + 1 + channel * 2, msb);
	if (ret)
		return -EIO;

	return len;
}