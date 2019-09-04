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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACNTL1 ; 
 int /*<<< orphan*/  ACNTL1_PDN_MASK ; 
 int /*<<< orphan*/  ACNTL2 ; 
 int /*<<< orphan*/  ACNTL2_PDN_MASK ; 
 int CLK_PDN ; 
 int C_PDN ; 
 int PLL_PDN ; 
 int Y_PDN ; 
 int tw9910_mask_set (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tw9910_power(struct i2c_client *client, int enable)
{
	int ret;
	u8 acntl1;
	u8 acntl2;

	if (enable) {
		acntl1 = 0;
		acntl2 = 0;
	} else {
		acntl1 = CLK_PDN | Y_PDN | C_PDN;
		acntl2 = PLL_PDN;
	}

	ret = tw9910_mask_set(client, ACNTL1, ACNTL1_PDN_MASK, acntl1);
	if (ret < 0)
		return ret;

	return tw9910_mask_set(client, ACNTL2, ACNTL2_PDN_MASK, acntl2);
}