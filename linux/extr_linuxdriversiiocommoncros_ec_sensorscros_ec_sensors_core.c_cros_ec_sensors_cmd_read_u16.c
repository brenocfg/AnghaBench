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
typedef  int /*<<< orphan*/  u16 ;
struct cros_ec_device {int (* cmd_readmem ) (struct cros_ec_device*,unsigned int,int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int stub1 (struct cros_ec_device*,unsigned int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_sensors_cmd_read_u16(struct cros_ec_device *ec,
					 unsigned int offset, u16 *dest)
{
	__le16 tmp;
	int ret = ec->cmd_readmem(ec, offset, 2, &tmp);

	if (ret >= 0)
		*dest = le16_to_cpu(tmp);

	return ret;
}