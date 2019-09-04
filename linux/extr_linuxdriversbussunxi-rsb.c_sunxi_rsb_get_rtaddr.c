#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ hwaddr; int /*<<< orphan*/  rtaddr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* sunxi_rsb_addr_maps ; 

__attribute__((used)) static u8 sunxi_rsb_get_rtaddr(u16 hwaddr)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(sunxi_rsb_addr_maps); i++)
		if (hwaddr == sunxi_rsb_addr_maps[i].hwaddr)
			return sunxi_rsb_addr_maps[i].rtaddr;

	return 0; /* 0 is an invalid runtime address */
}