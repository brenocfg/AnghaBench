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
typedef  unsigned char u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ntb_dev {int dummy; } ;
struct idt_ntb_dev {unsigned char peer_cnt; } ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;

/* Variables and functions */
 int GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDT_NT_PCIELCTLSTS ; 
 int /*<<< orphan*/  PCIELCTLSTS_CLS ; 
 int /*<<< orphan*/  PCIELCTLSTS_NLW ; 
 int /*<<< orphan*/  idt_nt_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_ntb_local_link_is_up (struct idt_ntb_dev*) ; 
 scalar_t__ idt_ntb_peer_link_is_up (struct idt_ntb_dev*,unsigned char) ; 
 struct idt_ntb_dev* to_ndev_ntb (struct ntb_dev*) ; 

__attribute__((used)) static u64 idt_ntb_link_is_up(struct ntb_dev *ntb,
			      enum ntb_speed *speed, enum ntb_width *width)
{
	struct idt_ntb_dev *ndev = to_ndev_ntb(ntb);
	unsigned char pidx;
	u64 status;
	u32 data;

	/* Retrieve the local link speed and width */
	if (speed != NULL || width != NULL) {
		data = idt_nt_read(ndev, IDT_NT_PCIELCTLSTS);
		if (speed != NULL)
			*speed = GET_FIELD(PCIELCTLSTS_CLS, data);
		if (width != NULL)
			*width = GET_FIELD(PCIELCTLSTS_NLW, data);
	}

	/* If local NTB link isn't up then all the links are considered down */
	if (!idt_ntb_local_link_is_up(ndev))
		return 0;

	/* Collect all the peer ports link states into the bitfield */
	status = 0;
	for (pidx = 0; pidx < ndev->peer_cnt; pidx++) {
		if (idt_ntb_peer_link_is_up(ndev, pidx))
			status |= ((u64)1 << pidx);
	}

	return status;
}