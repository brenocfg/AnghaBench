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
 int BYTE_EN_DWORD ; 
 int BYTE_EN_END_MASK ; 
 int BYTE_EN_START_MASK ; 
 int ENODEV ; 
 int EPERM ; 
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 int /*<<< orphan*/  rtl_set_unplug (struct r8152*) ; 
 int set_registers (struct r8152*,int,int,int,void*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int generic_ocp_write(struct r8152 *tp, u16 index, u16 byteen,
			     u16 size, void *data, u16 type)
{
	int ret;
	u16 byteen_start, byteen_end, byen;
	u16 limit = 512;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	/* both size and indix must be 4 bytes align */
	if ((size & 3) || !size || (index & 3) || !data)
		return -EPERM;

	if ((u32)index + (u32)size > 0xffff)
		return -EPERM;

	byteen_start = byteen & BYTE_EN_START_MASK;
	byteen_end = byteen & BYTE_EN_END_MASK;

	byen = byteen_start | (byteen_start << 4);
	ret = set_registers(tp, index, type | byen, 4, data);
	if (ret < 0)
		goto error1;

	index += 4;
	data += 4;
	size -= 4;

	if (size) {
		size -= 4;

		while (size) {
			if (size > limit) {
				ret = set_registers(tp, index,
						    type | BYTE_EN_DWORD,
						    limit, data);
				if (ret < 0)
					goto error1;

				index += limit;
				data += limit;
				size -= limit;
			} else {
				ret = set_registers(tp, index,
						    type | BYTE_EN_DWORD,
						    size, data);
				if (ret < 0)
					goto error1;

				index += size;
				data += size;
				size = 0;
				break;
			}
		}

		byen = byteen_end | (byteen_end >> 4);
		ret = set_registers(tp, index, type | byen, 4, data);
		if (ret < 0)
			goto error1;
	}

error1:
	if (ret == -ENODEV)
		rtl_set_unplug(tp);

	return ret;
}