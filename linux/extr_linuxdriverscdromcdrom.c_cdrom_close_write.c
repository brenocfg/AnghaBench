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
struct cdrom_device_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int cdrom_close_write(struct cdrom_device_info *cdi)
{
#if 0
	return cdrom_flush_cache(cdi);
#else
	return 0;
#endif
}