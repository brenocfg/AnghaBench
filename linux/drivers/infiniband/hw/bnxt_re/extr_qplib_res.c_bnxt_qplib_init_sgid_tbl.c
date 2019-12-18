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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct bnxt_qplib_sgid_tbl {size_t max; int /*<<< orphan*/  hw_id; TYPE_1__* tbl; } ;
struct TYPE_2__ {int vlan_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void bnxt_qplib_init_sgid_tbl(struct bnxt_qplib_sgid_tbl *sgid_tbl,
				     struct net_device *netdev)
{
	u32 i;

	for (i = 0; i < sgid_tbl->max; i++)
		sgid_tbl->tbl[i].vlan_id = 0xffff;

	memset(sgid_tbl->hw_id, -1, sizeof(u16) * sgid_tbl->max);
}