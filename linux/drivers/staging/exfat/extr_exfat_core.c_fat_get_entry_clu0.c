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
struct dos_dentry_t {int /*<<< orphan*/  start_clu_lo; int /*<<< orphan*/  start_clu_hi; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int GET16_A (int /*<<< orphan*/ ) ; 

u32 fat_get_entry_clu0(struct dentry_t *p_entry)
{
	struct dos_dentry_t *ep = (struct dos_dentry_t *)p_entry;

	return ((u32)GET16_A(ep->start_clu_hi) << 16) |
		GET16_A(ep->start_clu_lo);
}