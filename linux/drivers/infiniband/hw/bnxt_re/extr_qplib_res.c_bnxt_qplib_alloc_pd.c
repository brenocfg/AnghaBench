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
typedef  scalar_t__ u32 ;
struct bnxt_qplib_pd_tbl {scalar_t__ max; int /*<<< orphan*/  tbl; } ;
struct bnxt_qplib_pd {scalar_t__ id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_bit (int /*<<< orphan*/ ,scalar_t__) ; 

int bnxt_qplib_alloc_pd(struct bnxt_qplib_pd_tbl *pdt, struct bnxt_qplib_pd *pd)
{
	u32 bit_num;

	bit_num = find_first_bit(pdt->tbl, pdt->max);
	if (bit_num == pdt->max)
		return -ENOMEM;

	/* Found unused PD */
	clear_bit(bit_num, pdt->tbl);
	pd->id = bit_num;
	return 0;
}