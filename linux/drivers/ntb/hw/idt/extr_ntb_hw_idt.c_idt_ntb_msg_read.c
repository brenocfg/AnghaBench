#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct ntb_dev {int dummy; } ;
struct idt_ntb_dev {int* part_idx_map; } ;
struct TYPE_4__ {TYPE_1__* msgs; } ;
struct TYPE_3__ {int /*<<< orphan*/  in; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int EINVAL ; 
 int IDT_MSG_CNT ; 
 size_t idt_nt_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 
 TYPE_2__ ntdata_tbl ; 
 struct idt_ntb_dev* to_ndev_ntb (struct ntb_dev*) ; 

__attribute__((used)) static u32 idt_ntb_msg_read(struct ntb_dev *ntb, int *pidx, int midx)
{
	struct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	if (midx < 0 || IDT_MSG_CNT <= midx)
		return ~(u32)0;

	/* Retrieve source port index of the message */
	if (pidx != NULL) {
		u32 srcpart;

		srcpart = idt_nt_read(ndev, ntdata_tbl.msgs[midx].src);
		*pidx = ndev->part_idx_map[srcpart];

		/* Sanity check partition index (for initial case) */
		if (*pidx == -EINVAL)
			*pidx = 0;
	}

	/* Retrieve data of the corresponding message register */
	return idt_nt_read(ndev, ntdata_tbl.msgs[midx].in);
}