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
 int /*<<< orphan*/  ISL29003_REG_COMMAND ; 
 int /*<<< orphan*/  ISL29003_RES_MASK ; 
 int /*<<< orphan*/  ISL29003_RES_SHIFT ; 
 int __isl29003_read_reg (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isl29003_get_mode(struct i2c_client *client)
{
	return __isl29003_read_reg(client, ISL29003_REG_COMMAND,
		ISL29003_RES_MASK, ISL29003_RES_SHIFT);
}