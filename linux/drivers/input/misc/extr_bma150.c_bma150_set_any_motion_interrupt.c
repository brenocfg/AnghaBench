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
struct bma150_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMA150_ADV_INT_EN_MSK ; 
 int /*<<< orphan*/  BMA150_ADV_INT_EN_POS ; 
 int /*<<< orphan*/  BMA150_ADV_INT_EN_REG ; 
 int /*<<< orphan*/  BMA150_ANY_MOTION_DUR_MSK ; 
 int /*<<< orphan*/  BMA150_ANY_MOTION_DUR_POS ; 
 int /*<<< orphan*/  BMA150_ANY_MOTION_DUR_REG ; 
 int /*<<< orphan*/  BMA150_ANY_MOTION_EN_MSK ; 
 int /*<<< orphan*/  BMA150_ANY_MOTION_EN_POS ; 
 int /*<<< orphan*/  BMA150_ANY_MOTION_EN_REG ; 
 int /*<<< orphan*/  BMA150_ANY_MOTION_THRES_REG ; 
 int bma150_set_reg_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bma150_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bma150_set_any_motion_interrupt(struct bma150_data *bma150,
						u8 enable, u8 dur, u8 thres)
{
	int error;

	error = bma150_set_reg_bits(bma150->client, dur,
				BMA150_ANY_MOTION_DUR_POS,
				BMA150_ANY_MOTION_DUR_MSK,
				BMA150_ANY_MOTION_DUR_REG);
	if (error)
		return error;

	error = bma150_write_byte(bma150->client,
				BMA150_ANY_MOTION_THRES_REG, thres);
	if (error)
		return error;

	error = bma150_set_reg_bits(bma150->client, !!enable,
				BMA150_ADV_INT_EN_POS, BMA150_ADV_INT_EN_MSK,
				BMA150_ADV_INT_EN_REG);
	if (error)
		return error;

	return bma150_set_reg_bits(bma150->client, !!enable,
				BMA150_ANY_MOTION_EN_POS,
				BMA150_ANY_MOTION_EN_MSK,
				BMA150_ANY_MOTION_EN_REG);
}