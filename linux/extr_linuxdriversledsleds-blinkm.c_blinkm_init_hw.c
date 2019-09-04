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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLM_GO_RGB ; 
 int /*<<< orphan*/  BLM_STOP_SCRIPT ; 
 int blinkm_transfer_hw (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blinkm_init_hw(struct i2c_client *client)
{
	int ret;
	ret = blinkm_transfer_hw(client, BLM_STOP_SCRIPT);
	ret = blinkm_transfer_hw(client, BLM_GO_RGB);
}