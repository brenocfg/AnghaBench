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
 int /*<<< orphan*/  bnxt_hwrm_resource_free (struct bnxt*,int,int) ; 

__attribute__((used)) static int bnxt_shutdown_nic(struct bnxt *bp, bool irq_re_init)
{
	bnxt_hwrm_resource_free(bp, 1, irq_re_init);
	return 0;
}