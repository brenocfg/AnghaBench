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
typedef  int u32 ;
struct bnxt_qplib_res {int dummy; } ;
struct bnxt_qplib_pd_tbl {int max; scalar_t__ tbl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int bnxt_qplib_alloc_pd_tbl(struct bnxt_qplib_res *res,
				   struct bnxt_qplib_pd_tbl *pdt,
				   u32 max)
{
	u32 bytes;

	bytes = max >> 3;
	if (!bytes)
		bytes = 1;
	pdt->tbl = kmalloc(bytes, GFP_KERNEL);
	if (!pdt->tbl)
		return -ENOMEM;

	pdt->max = max;
	memset((u8 *)pdt->tbl, 0xFF, bytes);

	return 0;
}