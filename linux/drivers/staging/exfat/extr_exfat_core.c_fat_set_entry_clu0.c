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
struct dos_dentry_t {int /*<<< orphan*/  start_clu_hi; int /*<<< orphan*/  start_clu_lo; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_16 (int) ; 
 int /*<<< orphan*/  SET16_A (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fat_set_entry_clu0(struct dentry_t *p_entry, u32 start_clu)
{
	struct dos_dentry_t *ep = (struct dos_dentry_t *)p_entry;

	SET16_A(ep->start_clu_lo, CLUSTER_16(start_clu));
	SET16_A(ep->start_clu_hi, CLUSTER_16(start_clu >> 16));
}