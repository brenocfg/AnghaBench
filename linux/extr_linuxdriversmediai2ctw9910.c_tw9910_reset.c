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
 int /*<<< orphan*/  ACNTL1 ; 
 int /*<<< orphan*/  SRESET ; 
 int /*<<< orphan*/  tw9910_mask_set (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void tw9910_reset(struct i2c_client *client)
{
	tw9910_mask_set(client, ACNTL1, SRESET, SRESET);
	usleep_range(1000, 5000);
}