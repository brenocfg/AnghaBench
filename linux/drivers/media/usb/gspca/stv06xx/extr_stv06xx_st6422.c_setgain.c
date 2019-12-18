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
 int stv06xx_write_bridge (struct sd*,int,int) ; 

__attribute__((used)) static int setgain(struct sd *sd, u8 gain)
{
	int err;

	/* Set red, green, blue, gain */
	err = stv06xx_write_bridge(sd, 0x0509, gain);
	if (err < 0)
		return err;

	err = stv06xx_write_bridge(sd, 0x050a, gain);
	if (err < 0)
		return err;

	err = stv06xx_write_bridge(sd, 0x050b, gain);
	if (err < 0)
		return err;

	/* 2 mystery writes */
	err = stv06xx_write_bridge(sd, 0x050c, 0x2a);
	if (err < 0)
		return err;

	return stv06xx_write_bridge(sd, 0x050d, 0x01);
}