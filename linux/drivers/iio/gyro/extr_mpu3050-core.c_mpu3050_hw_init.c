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
struct mpu3050 {int /*<<< orphan*/  dev; int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  otp ;

/* Variables and functions */
 int /*<<< orphan*/  MPU3050_INT_CFG ; 
 int MPU3050_MEM_OTP_BANK_0 ; 
 int MPU3050_MEM_PRFTCH ; 
 int MPU3050_MEM_USER_BANK ; 
 int /*<<< orphan*/  MPU3050_PWR_MGM ; 
 int /*<<< orphan*/  MPU3050_PWR_MGM_CLKSEL_MASK ; 
 int /*<<< orphan*/  MPU3050_PWR_MGM_PLL_Z ; 
 int /*<<< orphan*/  MPU3050_PWR_MGM_RESET ; 
 int /*<<< orphan*/  add_device_randomness (int*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int,int,int,int) ; 
 int mpu3050_read_mem (struct mpu3050*,int,int /*<<< orphan*/ ,int,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpu3050_hw_init(struct mpu3050 *mpu3050)
{
	int ret;
	u8 otp[8];

	/* Reset */
	ret = regmap_update_bits(mpu3050->map,
				 MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_RESET,
				 MPU3050_PWR_MGM_RESET);
	if (ret)
		return ret;

	/* Turn on the PLL */
	ret = regmap_update_bits(mpu3050->map,
				 MPU3050_PWR_MGM,
				 MPU3050_PWR_MGM_CLKSEL_MASK,
				 MPU3050_PWR_MGM_PLL_Z);
	if (ret)
		return ret;

	/* Disable IRQs */
	ret = regmap_write(mpu3050->map,
			   MPU3050_INT_CFG,
			   0);
	if (ret)
		return ret;

	/* Read out the 8 bytes of OTP (one-time-programmable) memory */
	ret = mpu3050_read_mem(mpu3050,
			       (MPU3050_MEM_PRFTCH |
				MPU3050_MEM_USER_BANK |
				MPU3050_MEM_OTP_BANK_0),
			       0,
			       sizeof(otp),
			       otp);
	if (ret)
		return ret;

	/* This is device-unique data so it goes into the entropy pool */
	add_device_randomness(otp, sizeof(otp));

	dev_info(mpu3050->dev,
		 "die ID: %04X, wafer ID: %02X, A lot ID: %04X, "
		 "W lot ID: %03X, WP ID: %01X, rev ID: %02X\n",
		 /* Die ID, bits 0-12 */
		 (otp[1] << 8 | otp[0]) & 0x1fff,
		 /* Wafer ID, bits 13-17 */
		 ((otp[2] << 8 | otp[1]) & 0x03e0) >> 5,
		 /* A lot ID, bits 18-33 */
		 ((otp[4] << 16 | otp[3] << 8 | otp[2]) & 0x3fffc) >> 2,
		 /* W lot ID, bits 34-45 */
		 ((otp[5] << 8 | otp[4]) & 0x3ffc) >> 2,
		 /* WP ID, bits 47-49 */
		 ((otp[6] << 8 | otp[5]) & 0x0380) >> 7,
		 /* rev ID, bits 50-55 */
		 otp[6] >> 2);

	return 0;
}