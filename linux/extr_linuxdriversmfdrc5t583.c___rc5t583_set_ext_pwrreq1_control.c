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
typedef  int uint8_t ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned int ds_pos_bit; int reg_add; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int RC5T583_DS_DC0 ; 
 int RC5T583_DS_LDO4 ; 
 int RICOH_ONOFFSEL_REG ; 
 int RICOH_SWCTL_REG ; 
 TYPE_1__* deepsleep_data ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int rc5t583_read (struct device*,int,int*) ; 
 int rc5t583_set_bits (struct device*,int,int) ; 
 int rc5t583_write (struct device*,int,int) ; 

__attribute__((used)) static int __rc5t583_set_ext_pwrreq1_control(struct device *dev,
	int id, int ext_pwr, int slots)
{
	int ret;
	uint8_t sleepseq_val = 0;
	unsigned int en_bit;
	unsigned int slot_bit;

	if (id == RC5T583_DS_DC0) {
		dev_err(dev, "PWRREQ1 is invalid control for rail %d\n", id);
		return -EINVAL;
	}

	en_bit = deepsleep_data[id].ds_pos_bit;
	slot_bit = en_bit + 1;
	ret = rc5t583_read(dev, deepsleep_data[id].reg_add, &sleepseq_val);
	if (ret < 0) {
		dev_err(dev, "Error in reading reg 0x%x\n",
				deepsleep_data[id].reg_add);
		return ret;
	}

	sleepseq_val &= ~(0xF << en_bit);
	sleepseq_val |= BIT(en_bit);
	sleepseq_val |= ((slots & 0x7) << slot_bit);
	ret = rc5t583_set_bits(dev, RICOH_ONOFFSEL_REG, BIT(1));
	if (ret < 0) {
		dev_err(dev, "Error in updating the 0x%02x register\n",
				RICOH_ONOFFSEL_REG);
		return ret;
	}

	ret = rc5t583_write(dev, deepsleep_data[id].reg_add, sleepseq_val);
	if (ret < 0) {
		dev_err(dev, "Error in writing reg 0x%x\n",
				deepsleep_data[id].reg_add);
		return ret;
	}

	if (id == RC5T583_DS_LDO4) {
		ret = rc5t583_write(dev, RICOH_SWCTL_REG, 0x1);
		if (ret < 0)
			dev_err(dev, "Error in writing reg 0x%x\n",
				RICOH_SWCTL_REG);
	}
	return ret;
}