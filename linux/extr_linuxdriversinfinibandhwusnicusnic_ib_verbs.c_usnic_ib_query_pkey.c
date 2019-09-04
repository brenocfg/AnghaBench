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
typedef  int u16 ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

int usnic_ib_query_pkey(struct ib_device *ibdev, u8 port, u16 index,
				u16 *pkey)
{
	if (index > 1)
		return -EINVAL;

	*pkey = 0xffff;
	return 0;
}