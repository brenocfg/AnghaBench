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
struct dps310_data {void* c30; void* c21; void* c20; void* c11; void* c01; void* c10; void* c00; void* c1; void* c0; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  coef ;

/* Variables and functions */
 int /*<<< orphan*/  DPS310_COEF_BASE ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 void* sign_extend32 (int,int) ; 

__attribute__((used)) static int dps310_get_coefs(struct dps310_data *data)
{
	int rc;
	u8 coef[18];
	u32 c0, c1;
	u32 c00, c10, c20, c30, c01, c11, c21;

	/* Read all sensor calibration coefficients from the COEF registers. */
	rc = regmap_bulk_read(data->regmap, DPS310_COEF_BASE, coef,
			      sizeof(coef));
	if (rc < 0)
		return rc;

	/*
	 * Calculate temperature calibration coefficients c0 and c1. The
	 * numbers are 12-bit 2's complement numbers.
	 */
	c0 = (coef[0] << 4) | (coef[1] >> 4);
	data->c0 = sign_extend32(c0, 11);

	c1 = ((coef[1] & GENMASK(3, 0)) << 8) | coef[2];
	data->c1 = sign_extend32(c1, 11);

	/*
	 * Calculate pressure calibration coefficients. c00 and c10 are 20 bit
	 * 2's complement numbers, while the rest are 16 bit 2's complement
	 * numbers.
	 */
	c00 = (coef[3] << 12) | (coef[4] << 4) | (coef[5] >> 4);
	data->c00 = sign_extend32(c00, 19);

	c10 = ((coef[5] & GENMASK(3, 0)) << 16) | (coef[6] << 8) | coef[7];
	data->c10 = sign_extend32(c10, 19);

	c01 = (coef[8] << 8) | coef[9];
	data->c01 = sign_extend32(c01, 15);

	c11 = (coef[10] << 8) | coef[11];
	data->c11 = sign_extend32(c11, 15);

	c20 = (coef[12] << 8) | coef[13];
	data->c20 = sign_extend32(c20, 15);

	c21 = (coef[14] << 8) | coef[15];
	data->c21 = sign_extend32(c21, 15);

	c30 = (coef[16] << 8) | coef[17];
	data->c30 = sign_extend32(c30, 15);

	return 0;
}