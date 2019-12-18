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
typedef  int u32 ;
typedef  int u16 ;
struct r8152 {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 int get_registers (struct r8152*,int,int,int,void*) ; 
 int /*<<< orphan*/  rtl_set_unplug (struct r8152*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int generic_ocp_read(struct r8152 *tp, u16 index, u16 size,
			    void *data, u16 type)
{
	u16 limit = 64;
	int ret = 0;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	/* both size and indix must be 4 bytes align */
	if ((size & 3) || !size || (index & 3) || !data)
		return -EPERM;

	if ((u32)index + (u32)size > 0xffff)
		return -EPERM;

	while (size) {
		if (size > limit) {
			ret = get_registers(tp, index, type, limit, data);
			if (ret < 0)
				break;

			index += limit;
			data += limit;
			size -= limit;
		} else {
			ret = get_registers(tp, index, type, size, data);
			if (ret < 0)
				break;

			index += size;
			data += size;
			size = 0;
			break;
		}
	}

	if (ret == -ENODEV)
		rtl_set_unplug(tp);

	return ret;
}