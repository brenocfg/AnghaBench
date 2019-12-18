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
typedef  int /*<<< orphan*/  u8 ;
struct cros_ec_device {int (* cmd_readmem ) (struct cros_ec_device*,unsigned int,int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct cros_ec_device*,unsigned int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_sensors_cmd_read_u8(struct cros_ec_device *ec,
				       unsigned int offset, u8 *dest)
{
	return ec->cmd_readmem(ec, offset, 1, dest);
}