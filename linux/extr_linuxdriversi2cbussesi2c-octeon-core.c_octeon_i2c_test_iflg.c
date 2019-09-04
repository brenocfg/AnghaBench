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
 int TWSI_CTL_IFLG ; 
 int octeon_i2c_ctl_read (struct octeon_i2c*) ; 

__attribute__((used)) static bool octeon_i2c_test_iflg(struct octeon_i2c *i2c)
{
	return (octeon_i2c_ctl_read(i2c) & TWSI_CTL_IFLG);
}