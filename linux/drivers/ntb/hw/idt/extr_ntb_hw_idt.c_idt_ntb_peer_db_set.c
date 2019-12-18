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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ntb_dev {int dummy; } ;
struct idt_ntb_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IDT_DBELL_MASK ; 
 int /*<<< orphan*/  IDT_NT_OUTDBELLSET ; 
 int /*<<< orphan*/  idt_nt_write (struct idt_ntb_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct idt_ntb_dev* to_ndev_ntb (struct ntb_dev*) ; 

__attribute__((used)) static int idt_ntb_peer_db_set(struct ntb_dev *ntb, u64 db_bits)
{
	struct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	if (db_bits & ~(u64)IDT_DBELL_MASK)
		return -EINVAL;

	idt_nt_write(ndev, IDT_NT_OUTDBELLSET, (u32)db_bits);
	return 0;
}