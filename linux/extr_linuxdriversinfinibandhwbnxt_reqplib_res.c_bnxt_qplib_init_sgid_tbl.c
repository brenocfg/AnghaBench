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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct bnxt_qplib_sgid_tbl {int max; int /*<<< orphan*/  hw_id; int /*<<< orphan*/  tbl; } ;
struct bnxt_qplib_gid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void bnxt_qplib_init_sgid_tbl(struct bnxt_qplib_sgid_tbl *sgid_tbl,
				     struct net_device *netdev)
{
	memset(sgid_tbl->tbl, 0, sizeof(struct bnxt_qplib_gid) * sgid_tbl->max);
	memset(sgid_tbl->hw_id, -1, sizeof(u16) * sgid_tbl->max);
}