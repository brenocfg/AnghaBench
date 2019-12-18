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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct dos_dentry_t {int /*<<< orphan*/  size; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET32_A (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fat_set_entry_size(struct dentry_t *p_entry, u64 size)
{
	struct dos_dentry_t *ep = (struct dos_dentry_t *)p_entry;

	SET32_A(ep->size, (u32)size);
}