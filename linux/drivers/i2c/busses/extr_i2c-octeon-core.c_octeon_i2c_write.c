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
struct octeon_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWSI_CTL_ENAB ; 
 int octeon_i2c_check_status (struct octeon_i2c*,int) ; 
 int /*<<< orphan*/  octeon_i2c_ctl_write (struct octeon_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  octeon_i2c_data_write (struct octeon_i2c*,int const) ; 
 int octeon_i2c_wait (struct octeon_i2c*) ; 

__attribute__((used)) static int octeon_i2c_write(struct octeon_i2c *i2c, int target,
			    const u8 *data, int length)
{
	int i, result;

	octeon_i2c_data_write(i2c, target << 1);
	octeon_i2c_ctl_write(i2c, TWSI_CTL_ENAB);

	result = octeon_i2c_wait(i2c);
	if (result)
		return result;

	for (i = 0; i < length; i++) {
		result = octeon_i2c_check_status(i2c, false);
		if (result)
			return result;

		octeon_i2c_data_write(i2c, data[i]);
		octeon_i2c_ctl_write(i2c, TWSI_CTL_ENAB);

		result = octeon_i2c_wait(i2c);
		if (result)
			return result;
	}

	return 0;
}