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
struct bnxt {int nr_vnics; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_hwrm_vnic_set_rss (struct bnxt*,int,int) ; 

__attribute__((used)) static void bnxt_hwrm_clear_vnic_rss(struct bnxt *bp)
{
	int i;

	for (i = 0; i < bp->nr_vnics; i++)
		bnxt_hwrm_vnic_set_rss(bp, i, false);
}