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
struct genwqe_dev {int slu_unitcfg; } ;

/* Variables and functions */

bool genwqe_need_err_masking(struct genwqe_dev *cd)
{
	return (cd->slu_unitcfg & 0xFFFF0ull) < 0x32170ull;
}