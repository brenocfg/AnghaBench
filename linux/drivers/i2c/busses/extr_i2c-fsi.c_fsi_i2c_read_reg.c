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
typedef  int /*<<< orphan*/  u32 ;
struct fsi_device {int dummy; } ;
typedef  int /*<<< orphan*/  data_be ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int fsi_device_read (struct fsi_device*,unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fsi_i2c_read_reg(struct fsi_device *fsi, unsigned int reg,
			    u32 *data)
{
	int rc;
	__be32 data_be;

	rc = fsi_device_read(fsi, reg, &data_be, sizeof(data_be));
	if (rc)
		return rc;

	*data = be32_to_cpu(data_be);

	return 0;
}