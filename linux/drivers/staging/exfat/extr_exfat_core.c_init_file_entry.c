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
typedef  int /*<<< orphan*/  u32 ;
struct timestamp_t {int dummy; } ;
struct file_dentry_t {scalar_t__ access_time_ms; scalar_t__ modify_time_ms; scalar_t__ create_time_ms; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TM_ACCESS ; 
 int /*<<< orphan*/  TM_CREATE ; 
 int /*<<< orphan*/  TM_MODIFY ; 
 int /*<<< orphan*/  exfat_set_entry_time (struct dentry_t*,struct timestamp_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exfat_set_entry_type (struct dentry_t*,int /*<<< orphan*/ ) ; 
 struct timestamp_t* tm_current (struct timestamp_t*) ; 

void init_file_entry(struct file_dentry_t *ep, u32 type)
{
	struct timestamp_t tm, *tp;

	exfat_set_entry_type((struct dentry_t *)ep, type);

	tp = tm_current(&tm);
	exfat_set_entry_time((struct dentry_t *)ep, tp, TM_CREATE);
	exfat_set_entry_time((struct dentry_t *)ep, tp, TM_MODIFY);
	exfat_set_entry_time((struct dentry_t *)ep, tp, TM_ACCESS);
	ep->create_time_ms = 0;
	ep->modify_time_ms = 0;
	ep->access_time_ms = 0;
}