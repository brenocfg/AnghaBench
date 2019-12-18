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
struct ad5933_state {unsigned char ctrl_lb; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 unsigned char AD5933_CTRL_RESET ; 
 int /*<<< orphan*/  AD5933_REG_CONTROL_LB ; 
 int ad5933_i2c_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*) ; 

__attribute__((used)) static int ad5933_reset(struct ad5933_state *st)
{
	unsigned char dat = st->ctrl_lb | AD5933_CTRL_RESET;

	return ad5933_i2c_write(st->client,
			AD5933_REG_CONTROL_LB, 1, &dat);
}