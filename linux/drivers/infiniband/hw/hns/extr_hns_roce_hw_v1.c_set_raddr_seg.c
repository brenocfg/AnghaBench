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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hns_roce_wqe_raddr_seg {scalar_t__ len; int /*<<< orphan*/  rkey; int /*<<< orphan*/  raddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_raddr_seg(struct hns_roce_wqe_raddr_seg *rseg, u64 remote_addr,
			  u32 rkey)
{
	rseg->raddr = cpu_to_le64(remote_addr);
	rseg->rkey  = cpu_to_le32(rkey);
	rseg->len   = 0;
}