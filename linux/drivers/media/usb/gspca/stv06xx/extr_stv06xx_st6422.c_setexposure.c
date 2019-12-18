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
struct sd {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int stv06xx_write_bridge (struct sd*,int,int) ; 

__attribute__((used)) static int setexposure(struct sd *sd, s16 expo)
{
	int err;

	err = stv06xx_write_bridge(sd, 0x143d, expo & 0xff);
	if (err < 0)
		return err;

	return stv06xx_write_bridge(sd, 0x143e, expo >> 8);
}