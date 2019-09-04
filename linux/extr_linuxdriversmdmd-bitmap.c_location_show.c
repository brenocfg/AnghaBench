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
struct TYPE_2__ {scalar_t__ offset; scalar_t__ file; } ;
struct mddev {TYPE_1__ bitmap_info; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t
location_show(struct mddev *mddev, char *page)
{
	ssize_t len;
	if (mddev->bitmap_info.file)
		len = sprintf(page, "file");
	else if (mddev->bitmap_info.offset)
		len = sprintf(page, "%+lld", (long long)mddev->bitmap_info.offset);
	else
		len = sprintf(page, "none");
	len += sprintf(page+len, "\n");
	return len;
}