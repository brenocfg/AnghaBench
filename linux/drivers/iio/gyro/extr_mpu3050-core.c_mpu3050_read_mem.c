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
typedef  int /*<<< orphan*/  u8 ;
struct mpu3050 {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPU3050_BANK_SEL ; 
 int /*<<< orphan*/  MPU3050_MEM_R_W ; 
 int /*<<< orphan*/  MPU3050_MEM_START_ADDR ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpu3050_read_mem(struct mpu3050 *mpu3050,
			    u8 bank,
			    u8 addr,
			    u8 len,
			    u8 *buf)
{
	int ret;

	ret = regmap_write(mpu3050->map,
			   MPU3050_BANK_SEL,
			   bank);
	if (ret)
		return ret;

	ret = regmap_write(mpu3050->map,
			   MPU3050_MEM_START_ADDR,
			   addr);
	if (ret)
		return ret;

	return regmap_bulk_read(mpu3050->map,
				MPU3050_MEM_R_W,
				buf,
				len);
}