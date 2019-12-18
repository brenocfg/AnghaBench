#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int high_part; int low_part; } ;
union ULARGE_INTEGER {unsigned long long quad_part; TYPE_1__ u; } ;
struct TYPE_6__ {int mask; void* vmid; int /*<<< orphan*/  mode; } ;
union TCP_WATCH_CNTL_BITS {TYPE_2__ bitfields; int /*<<< orphan*/  u32All; } ;
struct TYPE_8__ {int addr; } ;
union TCP_WATCH_ADDR_L_BITS {TYPE_4__ bitfields; scalar_t__ u32All; } ;
struct TYPE_7__ {int addr; } ;
union TCP_WATCH_ADDR_H_BITS {TYPE_3__ bitfields; scalar_t__ u32All; } ;
typedef  void* uint32_t ;
struct dbg_address_watch_info {int* watch_mask; int /*<<< orphan*/ * watch_mode; scalar_t__* watch_address; } ;

/* Variables and functions */
 int ADDRESS_WATCH_REG_ADDHIGH_MASK ; 
 int ADDRESS_WATCH_REG_ADDLOW_SHIFT ; 
 int /*<<< orphan*/  ADDRESS_WATCH_REG_CNTL_ATC_BIT ; 
 int ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int) ; 

__attribute__((used)) static void dbgdev_address_watch_set_registers(
			const struct dbg_address_watch_info *adw_info,
			union TCP_WATCH_ADDR_H_BITS *addrHi,
			union TCP_WATCH_ADDR_L_BITS *addrLo,
			union TCP_WATCH_CNTL_BITS *cntl,
			unsigned int index, unsigned int vmid)
{
	union ULARGE_INTEGER addr;

	addr.quad_part = 0;
	addrHi->u32All = 0;
	addrLo->u32All = 0;
	cntl->u32All = 0;

	if (adw_info->watch_mask)
		cntl->bitfields.mask =
			(uint32_t) (adw_info->watch_mask[index] &
					ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK);
	else
		cntl->bitfields.mask = ADDRESS_WATCH_REG_CNTL_DEFAULT_MASK;

	addr.quad_part = (unsigned long long) adw_info->watch_address[index];

	addrHi->bitfields.addr = addr.u.high_part &
					ADDRESS_WATCH_REG_ADDHIGH_MASK;
	addrLo->bitfields.addr =
			(addr.u.low_part >> ADDRESS_WATCH_REG_ADDLOW_SHIFT);

	cntl->bitfields.mode = adw_info->watch_mode[index];
	cntl->bitfields.vmid = (uint32_t) vmid;
	/* for now assume it is an ATC address */
	cntl->u32All |= ADDRESS_WATCH_REG_CNTL_ATC_BIT;

	pr_debug("\t\t%20s %08x\n", "set reg mask :", cntl->bitfields.mask);
	pr_debug("\t\t%20s %08x\n", "set reg add high :",
			addrHi->bitfields.addr);
	pr_debug("\t\t%20s %08x\n", "set reg add low :",
			addrLo->bitfields.addr);
}