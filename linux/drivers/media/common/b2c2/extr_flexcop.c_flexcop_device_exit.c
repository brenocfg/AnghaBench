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
struct flexcop_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flexcop_dvb_exit (struct flexcop_device*) ; 
 int /*<<< orphan*/  flexcop_frontend_exit (struct flexcop_device*) ; 
 int /*<<< orphan*/  flexcop_i2c_exit (struct flexcop_device*) ; 

void flexcop_device_exit(struct flexcop_device *fc)
{
	flexcop_frontend_exit(fc);
	flexcop_i2c_exit(fc);
	flexcop_dvb_exit(fc);
}