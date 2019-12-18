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
struct file_dentry_t {int /*<<< orphan*/  attr; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET16_A (int /*<<< orphan*/ ) ; 

u32 exfat_get_entry_attr(struct dentry_t *p_entry)
{
	struct file_dentry_t *ep = (struct file_dentry_t *)p_entry;

	return (u32)GET16_A(ep->attr);
}