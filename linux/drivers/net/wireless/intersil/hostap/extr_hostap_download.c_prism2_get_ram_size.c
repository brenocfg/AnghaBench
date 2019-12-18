#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* func; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* genesis_reset ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 scalar_t__ prism2_enable_genesis (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static int prism2_get_ram_size(local_info_t *local)
{
	int ret;

	/* Try to enable genesis mode; 0x1F for x8 SRAM or 0x0F for x16 SRAM */
	if (prism2_enable_genesis(local, 0x1f) == 0)
		ret = 8;
	else if (prism2_enable_genesis(local, 0x0f) == 0)
		ret = 16;
	else
		ret = -1;

	/* Disable genesis mode */
	local->func->genesis_reset(local, ret == 16 ? 0x07 : 0x17);

	return ret;
}