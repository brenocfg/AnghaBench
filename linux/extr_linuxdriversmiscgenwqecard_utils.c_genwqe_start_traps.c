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
struct genwqe_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_SLC_MISC_DEBUG ; 
 int /*<<< orphan*/  IO_SLC_MISC_DEBUG_CLR ; 
 int /*<<< orphan*/  __genwqe_writeq (struct genwqe_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ genwqe_need_err_masking (struct genwqe_dev*) ; 

void genwqe_start_traps(struct genwqe_dev *cd)
{
	__genwqe_writeq(cd, IO_SLC_MISC_DEBUG_CLR, 0xcull);

	if (genwqe_need_err_masking(cd))
		__genwqe_writeq(cd, IO_SLC_MISC_DEBUG, 0x0aull);
}