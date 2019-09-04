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
struct octeon_i2c {int dummy; } ;

/* Variables and functions */
 int TWSI_CTL_ENAB ; 
 int TWSI_CTL_STP ; 
 int /*<<< orphan*/  octeon_i2c_ctl_write (struct octeon_i2c*,int) ; 

__attribute__((used)) static void octeon_i2c_stop(struct octeon_i2c *i2c)
{
	octeon_i2c_ctl_write(i2c, TWSI_CTL_ENAB | TWSI_CTL_STP);
}