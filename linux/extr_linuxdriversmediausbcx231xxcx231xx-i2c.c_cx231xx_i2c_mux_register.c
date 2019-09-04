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
struct cx231xx {int /*<<< orphan*/  muxc; } ;

/* Variables and functions */
 int i2c_mux_add_adapter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int cx231xx_i2c_mux_register(struct cx231xx *dev, int mux_no)
{
	return i2c_mux_add_adapter(dev->muxc,
				   0,
				   mux_no /* chan_id */,
				   0 /* class */);
}