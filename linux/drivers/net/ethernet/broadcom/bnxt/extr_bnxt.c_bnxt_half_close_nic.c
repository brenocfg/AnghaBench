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
struct bnxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_free_mem (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_free_skbs (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_resource_free (struct bnxt*,int,int) ; 

void bnxt_half_close_nic(struct bnxt *bp)
{
	bnxt_hwrm_resource_free(bp, false, false);
	bnxt_free_skbs(bp);
	bnxt_free_mem(bp, false);
}