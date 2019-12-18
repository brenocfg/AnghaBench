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
typedef  int /*<<< orphan*/  u64 ;
struct strm_dentry_t {int /*<<< orphan*/  size; int /*<<< orphan*/  valid_size; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET64_A (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void exfat_set_entry_size(struct dentry_t *p_entry, u64 size)
{
	struct strm_dentry_t *ep = (struct strm_dentry_t *)p_entry;

	SET64_A(ep->valid_size, size);
	SET64_A(ep->size, size);
}