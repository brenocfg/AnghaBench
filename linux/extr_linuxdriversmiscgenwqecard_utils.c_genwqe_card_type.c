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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct genwqe_dev {int slu_unitcfg; } ;

/* Variables and functions */
 int IO_SLU_UNITCFG_TYPE_MASK ; 

u8 genwqe_card_type(struct genwqe_dev *cd)
{
	u64 card_type = cd->slu_unitcfg;

	return (u8)((card_type & IO_SLU_UNITCFG_TYPE_MASK) >> 20);
}