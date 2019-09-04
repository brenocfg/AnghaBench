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
struct sd {int dummy; } ;

/* Variables and functions */
 int i2c_r (struct sd*,int) ; 
 int /*<<< orphan*/  i2c_w (struct sd*,int,int) ; 

__attribute__((used)) static void i2c_w_mask(struct sd *sd,
			u8 reg,
			u8 value,
			u8 mask)
{
	int rc;
	u8 oldval;

	value &= mask;			/* Enforce mask on value */
	rc = i2c_r(sd, reg);
	if (rc < 0)
		return;
	oldval = rc & ~mask;		/* Clear the masked bits */
	value |= oldval;		/* Set the desired bits */
	i2c_w(sd, reg, value);
}