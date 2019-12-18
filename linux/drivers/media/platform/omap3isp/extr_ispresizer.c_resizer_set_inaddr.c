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
struct isp_res_device {int addr_base; int crop_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  __resizer_set_inaddr (struct isp_res_device*,int) ; 

__attribute__((used)) static void resizer_set_inaddr(struct isp_res_device *res, u32 addr)
{
	res->addr_base = addr;

	/* This will handle crop settings in stream off state */
	if (res->crop_offset)
		addr += res->crop_offset & ~0x1f;

	__resizer_set_inaddr(res, addr);
}