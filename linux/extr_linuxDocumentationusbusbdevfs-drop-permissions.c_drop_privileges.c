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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  USBDEVFS_DROP_PRIVILEGES ; 
 int ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void drop_privileges(int fd, uint32_t mask)
{
	int res;

	res = ioctl(fd, USBDEVFS_DROP_PRIVILEGES, &mask);
	if (res)
		printf("ERROR: USBDEVFS_DROP_PRIVILEGES returned %d\n", res);
	else
		printf("OK: privileges dropped!\n");
}