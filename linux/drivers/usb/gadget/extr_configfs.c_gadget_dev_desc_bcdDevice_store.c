#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  bcdDevice; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;
struct TYPE_6__ {TYPE_2__ cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int is_valid_bcd (int /*<<< orphan*/ ) ; 
 int kstrtou16 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* to_gadget_info (struct config_item*) ; 

__attribute__((used)) static ssize_t gadget_dev_desc_bcdDevice_store(struct config_item *item,
		const char *page, size_t len)
{
	u16 bcdDevice;
	int ret;

	ret = kstrtou16(page, 0, &bcdDevice);
	if (ret)
		return ret;
	ret = is_valid_bcd(bcdDevice);
	if (ret)
		return ret;

	to_gadget_info(item)->cdev.desc.bcdDevice = cpu_to_le16(bcdDevice);
	return len;
}