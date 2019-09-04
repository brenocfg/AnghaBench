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
struct bma150_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMA150_SW_RES_MSK ; 
 int /*<<< orphan*/  BMA150_SW_RES_POS ; 
 int /*<<< orphan*/  BMA150_SW_RES_REG ; 
 int bma150_set_reg_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bma150_soft_reset(struct bma150_data *bma150)
{
	int error;

	error = bma150_set_reg_bits(bma150->client, 1, BMA150_SW_RES_POS,
				BMA150_SW_RES_MSK, BMA150_SW_RES_REG);
	if (error)
		return error;

	usleep_range(2000, 2100);
	return 0;
}