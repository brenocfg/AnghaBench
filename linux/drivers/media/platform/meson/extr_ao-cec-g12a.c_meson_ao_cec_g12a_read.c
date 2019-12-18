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
typedef  int u32 ;
struct meson_ao_cec_g12a_device {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CECB_RW_ADDR ; 
 int CECB_RW_BUS_BUSY ; 
 int /*<<< orphan*/  CECB_RW_RD_DATA ; 
 int /*<<< orphan*/  CECB_RW_REG ; 
 unsigned int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int FIELD_PREP (int /*<<< orphan*/ ,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int meson_ao_cec_g12a_read(void *context, unsigned int addr,
				  unsigned int *data)
{
	struct meson_ao_cec_g12a_device *ao_cec = context;
	u32 reg = FIELD_PREP(CECB_RW_ADDR, addr);
	int ret = 0;

	ret = regmap_write(ao_cec->regmap, CECB_RW_REG, reg);
	if (ret)
		return ret;

	ret = regmap_read_poll_timeout(ao_cec->regmap, CECB_RW_REG, reg,
				       !(reg & CECB_RW_BUS_BUSY),
				       5, 1000);
	if (ret)
		return ret;

	ret = regmap_read(ao_cec->regmap, CECB_RW_REG, &reg);

	*data = FIELD_GET(CECB_RW_RD_DATA, reg);

	return ret;
}