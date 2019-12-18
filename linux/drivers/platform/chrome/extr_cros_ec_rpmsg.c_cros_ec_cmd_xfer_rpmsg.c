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
struct cros_ec_device {int dummy; } ;
struct cros_ec_command {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int cros_ec_cmd_xfer_rpmsg(struct cros_ec_device *ec_dev,
				  struct cros_ec_command *ec_msg)
{
	return -EINVAL;
}