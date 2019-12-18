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
struct iucv_path {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int iucv_path_accept (struct iucv_path*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsg_handler ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int smsg_path_pending(struct iucv_path *path, u8 *ipvmid, u8 *ipuser)
{
	if (strncmp(ipvmid, "*MSG    ", 8) != 0)
		return -EINVAL;
	/* Path pending from *MSG. */
	return iucv_path_accept(path, &smsg_handler, "SMSGIUCV        ", NULL);
}