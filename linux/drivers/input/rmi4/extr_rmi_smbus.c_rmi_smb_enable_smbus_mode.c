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
struct rmi_smb_xport {int dummy; } ;

/* Variables and functions */
 int rmi_smb_get_version (struct rmi_smb_xport*) ; 

__attribute__((used)) static int rmi_smb_enable_smbus_mode(struct rmi_smb_xport *rmi_smb)
{
	int retval;

	/* we need to get the smbus version to activate the touchpad */
	retval = rmi_smb_get_version(rmi_smb);
	if (retval < 0)
		return retval;

	return 0;
}