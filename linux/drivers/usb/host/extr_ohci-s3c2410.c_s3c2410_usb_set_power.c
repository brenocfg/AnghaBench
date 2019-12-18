#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct s3c2410_hcd_info {int /*<<< orphan*/  (* power_control ) (int,int) ;TYPE_1__* port; } ;
struct TYPE_2__ {int power; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,int) ; 

__attribute__((used)) static void s3c2410_usb_set_power(struct s3c2410_hcd_info *info,
				  int port, int to)
{
	if (info == NULL)
		return;

	if (info->power_control != NULL) {
		info->port[port-1].power = to;
		(info->power_control)(port-1, to);
	}
}