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
struct bnxt_vnic_info {int dummy; } ;
struct bnxt {int flags; int nr_vnics; int /*<<< orphan*/  vnic_info; scalar_t__ rx_nr_rings; } ;

/* Variables and functions */
 scalar_t__ BNXT_CHIP_TYPE_NITRO_A0 (struct bnxt*) ; 
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_RFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_alloc_vnics(struct bnxt *bp)
{
	int num_vnics = 1;

#ifdef CONFIG_RFS_ACCEL
	if ((bp->flags & (BNXT_FLAG_RFS | BNXT_FLAG_CHIP_P5)) == BNXT_FLAG_RFS)
		num_vnics += bp->rx_nr_rings;
#endif

	if (BNXT_CHIP_TYPE_NITRO_A0(bp))
		num_vnics++;

	bp->vnic_info = kcalloc(num_vnics, sizeof(struct bnxt_vnic_info),
				GFP_KERNEL);
	if (!bp->vnic_info)
		return -ENOMEM;

	bp->nr_vnics = num_vnics;
	return 0;
}