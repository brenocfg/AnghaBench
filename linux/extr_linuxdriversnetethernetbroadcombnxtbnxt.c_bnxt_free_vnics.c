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
struct bnxt {scalar_t__ nr_vnics; int /*<<< orphan*/ * vnic_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_free_vnics(struct bnxt *bp)
{
	kfree(bp->vnic_info);
	bp->vnic_info = NULL;
	bp->nr_vnics = 0;
}