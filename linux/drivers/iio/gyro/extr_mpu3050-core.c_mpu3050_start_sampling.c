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
struct mpu3050 {int fullscale; int lpf; int divisor; int /*<<< orphan*/  map; int /*<<< orphan*/ * calibration; } ;
typedef  int /*<<< orphan*/  raw_val ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int MPU3050_DLPF_CFG_SHIFT ; 
 int /*<<< orphan*/  MPU3050_DLPF_FS_SYNC ; 
 int MPU3050_EXT_SYNC_NONE ; 
 int MPU3050_EXT_SYNC_SHIFT ; 
 int MPU3050_FS_SHIFT ; 
 int /*<<< orphan*/  MPU3050_PWR_MGM ; 
 int /*<<< orphan*/  MPU3050_PWR_MGM_CLKSEL_MASK ; 
 int /*<<< orphan*/  MPU3050_PWR_MGM_PLL_Z ; 
 int /*<<< orphan*/  MPU3050_PWR_MGM_RESET ; 
 int /*<<< orphan*/  MPU3050_SMPLRT_DIV ; 
 int /*<<< orphan*/  MPU3050_X_OFFS_USR_H ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int mpu3050_get_freq (struct mpu3050*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mpu3050_start_sampling(struct mpu3050 *mpu3050)
{
	__be16 raw_val[3];
	int ret;
	int i;

	/* Reset */
	ret = regmap_update_bits(mpu3050->map, MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_RESET, MPU3050_PWR_MGM_RESET);
	if (ret)
		return ret;

	/* Turn on the Z-axis PLL */
	ret = regmap_update_bits(mpu3050->map, MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_CLKSEL_MASK,
				 MPU3050_PWR_MGM_PLL_Z);
	if (ret)
		return ret;

	/* Write calibration offset registers */
	for (i = 0; i < 3; i++)
		raw_val[i] = cpu_to_be16(mpu3050->calibration[i]);

	ret = regmap_bulk_write(mpu3050->map, MPU3050_X_OFFS_USR_H, raw_val,
				sizeof(raw_val));
	if (ret)
		return ret;

	/* Set low pass filter (sample rate), sync and full scale */
	ret = regmap_write(mpu3050->map, MPU3050_DLPF_FS_SYNC,
			   MPU3050_EXT_SYNC_NONE << MPU3050_EXT_SYNC_SHIFT |
			   mpu3050->fullscale << MPU3050_FS_SHIFT |
			   mpu3050->lpf << MPU3050_DLPF_CFG_SHIFT);
	if (ret)
		return ret;

	/* Set up sampling frequency */
	ret = regmap_write(mpu3050->map, MPU3050_SMPLRT_DIV, mpu3050->divisor);
	if (ret)
		return ret;

	/*
	 * Max 50 ms start-up time after setting DLPF_FS_SYNC
	 * according to the data sheet, then wait for the next sample
	 * at this frequency T = 1000/f ms.
	 */
	msleep(50 + 1000 / mpu3050_get_freq(mpu3050));

	return 0;
}