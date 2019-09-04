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
struct bma150_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMA150_BANDWIDTH_MSK ; 
 int /*<<< orphan*/  BMA150_BANDWIDTH_POS ; 
 int /*<<< orphan*/  BMA150_BANDWIDTH_REG ; 
 int bma150_set_reg_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bma150_set_bandwidth(struct bma150_data *bma150, u8 bw)
{
	return bma150_set_reg_bits(bma150->client, bw, BMA150_BANDWIDTH_POS,
				BMA150_BANDWIDTH_MSK, BMA150_BANDWIDTH_REG);
}