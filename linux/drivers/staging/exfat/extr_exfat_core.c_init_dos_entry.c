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
typedef  int u32 ;
struct timestamp_t {int dummy; } ;
struct dos_dentry_t {scalar_t__ create_time_ms; int /*<<< orphan*/  access_date; int /*<<< orphan*/  size; int /*<<< orphan*/  start_clu_hi; int /*<<< orphan*/  start_clu_lo; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_16 (int) ; 
 int /*<<< orphan*/  SET16_A (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET32_A (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TM_CREATE ; 
 int /*<<< orphan*/  TM_MODIFY ; 
 int /*<<< orphan*/  fat_set_entry_time (struct dentry_t*,struct timestamp_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fat_set_entry_type (struct dentry_t*,int) ; 
 struct timestamp_t* tm_current (struct timestamp_t*) ; 

void init_dos_entry(struct dos_dentry_t *ep, u32 type, u32 start_clu)
{
	struct timestamp_t tm, *tp;

	fat_set_entry_type((struct dentry_t *)ep, type);
	SET16_A(ep->start_clu_lo, CLUSTER_16(start_clu));
	SET16_A(ep->start_clu_hi, CLUSTER_16(start_clu >> 16));
	SET32_A(ep->size, 0);

	tp = tm_current(&tm);
	fat_set_entry_time((struct dentry_t *)ep, tp, TM_CREATE);
	fat_set_entry_time((struct dentry_t *)ep, tp, TM_MODIFY);
	SET16_A(ep->access_date, 0);
	ep->create_time_ms = 0;
}