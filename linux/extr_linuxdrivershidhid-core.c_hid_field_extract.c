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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hid_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __extract (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  hid_warn (struct hid_device const*,char*,unsigned int,int /*<<< orphan*/ ) ; 

u32 hid_field_extract(const struct hid_device *hid, u8 *report,
			unsigned offset, unsigned n)
{
	if (n > 32) {
		hid_warn(hid, "hid_field_extract() called with n (%d) > 32! (%s)\n",
			 n, current->comm);
		n = 32;
	}

	return __extract(report, offset, n);
}