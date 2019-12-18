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
typedef  scalar_t__ u8 ;
struct octeon_i2c {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ STAT_REP_START ; 
 scalar_t__ STAT_START ; 
 int TWSI_CTL_ENAB ; 
 int TWSI_CTL_STA ; 
 int /*<<< orphan*/  octeon_i2c_ctl_write (struct octeon_i2c*,int) ; 
 int /*<<< orphan*/  octeon_i2c_hlc_disable (struct octeon_i2c*) ; 
 int octeon_i2c_recovery (struct octeon_i2c*) ; 
 scalar_t__ octeon_i2c_stat_read (struct octeon_i2c*) ; 
 int octeon_i2c_wait (struct octeon_i2c*) ; 

__attribute__((used)) static int octeon_i2c_start(struct octeon_i2c *i2c)
{
	int ret;
	u8 stat;

	octeon_i2c_hlc_disable(i2c);

	octeon_i2c_ctl_write(i2c, TWSI_CTL_ENAB | TWSI_CTL_STA);
	ret = octeon_i2c_wait(i2c);
	if (ret)
		goto error;

	stat = octeon_i2c_stat_read(i2c);
	if (stat == STAT_START || stat == STAT_REP_START)
		/* START successful, bail out */
		return 0;

error:
	/* START failed, try to recover */
	ret = octeon_i2c_recovery(i2c);
	return (ret) ? ret : -EAGAIN;
}