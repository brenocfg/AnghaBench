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
struct mpc_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_MEN ; 
 int /*<<< orphan*/  writeccr (struct mpc_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mpc_i2c_stop(struct mpc_i2c *i2c)
{
	writeccr(i2c, CCR_MEN);
}