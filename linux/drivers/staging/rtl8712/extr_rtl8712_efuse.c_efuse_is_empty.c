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
typedef  int u8 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ efuse_one_byte_rw (struct _adapter*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u8 efuse_is_empty(struct _adapter *adapter, u8 *empty)
{
	u8 value, ret = true;

	/* read one byte to check if E-Fuse is empty */
	if (efuse_one_byte_rw(adapter, true, 0, &value)) {
		if (value == 0xFF)
			*empty = true;
		else
			*empty = false;
	} else {
		ret = false;
	}
	return ret;
}