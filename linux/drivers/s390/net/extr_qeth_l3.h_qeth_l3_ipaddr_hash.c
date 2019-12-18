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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ a4; TYPE_2__ a6; } ;
struct qeth_ipaddr {scalar_t__ proto; TYPE_3__ u; } ;

/* Variables and functions */
 scalar_t__ QETH_PROT_IPV4 ; 
 scalar_t__ QETH_PROT_IPV6 ; 
 int get_unaligned (int*) ; 

__attribute__((used)) static inline  u64 qeth_l3_ipaddr_hash(struct qeth_ipaddr *addr)
{
	u64  ret = 0;
	u8 *point;

	if (addr->proto == QETH_PROT_IPV6) {
		point = (u8 *) &addr->u.a6.addr;
		ret = get_unaligned((u64 *)point) ^
			get_unaligned((u64 *) (point + 8));
	}
	if (addr->proto == QETH_PROT_IPV4) {
		point = (u8 *) &addr->u.a4.addr;
		ret = get_unaligned((u32 *) point);
	}
	return ret;
}