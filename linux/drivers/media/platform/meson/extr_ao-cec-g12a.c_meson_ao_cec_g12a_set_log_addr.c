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
struct meson_ao_cec_g12a_device {int /*<<< orphan*/  regmap_cec; } ;
struct cec_adapter {struct meson_ao_cec_g12a_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CECB_LADD_HIGH ; 
 int /*<<< orphan*/  CECB_LADD_LOW ; 
 int CEC_LOG_ADDR_INVALID ; 
 int CEC_LOG_ADDR_UNREGISTERED ; 
 int EIO ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
meson_ao_cec_g12a_set_log_addr(struct cec_adapter *adap, u8 logical_addr)
{
	struct meson_ao_cec_g12a_device *ao_cec = adap->priv;
	int ret = 0;

	if (logical_addr == CEC_LOG_ADDR_INVALID) {
		/* Assume this will allways succeed */
		regmap_write(ao_cec->regmap_cec, CECB_LADD_LOW, 0);
		regmap_write(ao_cec->regmap_cec, CECB_LADD_HIGH, 0);

		return 0;
	} else if (logical_addr < 8) {
		ret = regmap_update_bits(ao_cec->regmap_cec, CECB_LADD_LOW,
					 BIT(logical_addr),
					 BIT(logical_addr));
	} else {
		ret = regmap_update_bits(ao_cec->regmap_cec, CECB_LADD_HIGH,
					 BIT(logical_addr - 8),
					 BIT(logical_addr - 8));
	}

	/* Always set Broadcast/Unregistered 15 address */
	ret |= regmap_update_bits(ao_cec->regmap_cec, CECB_LADD_HIGH,
				  BIT(CEC_LOG_ADDR_UNREGISTERED - 8),
				  BIT(CEC_LOG_ADDR_UNREGISTERED - 8));

	return ret ? -EIO : 0;
}