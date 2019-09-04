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
typedef  int /*<<< orphan*/  u16 ;
struct bnxt_qplib_pkey_tbl {int max; scalar_t__ active; int /*<<< orphan*/  tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnxt_qplib_cleanup_pkey_tbl(struct bnxt_qplib_pkey_tbl *pkey_tbl)
{
	memset(pkey_tbl->tbl, 0, sizeof(u16) * pkey_tbl->max);
	pkey_tbl->active = 0;
}