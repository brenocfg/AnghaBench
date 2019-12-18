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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct strm_dentry_t {int /*<<< orphan*/  size; int /*<<< orphan*/  valid_size; int /*<<< orphan*/  start_clu; int /*<<< orphan*/  flags; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET32_A (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET64_A (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_STREAM ; 
 int /*<<< orphan*/  exfat_set_entry_type (struct dentry_t*,int /*<<< orphan*/ ) ; 

void init_strm_entry(struct strm_dentry_t *ep, u8 flags, u32 start_clu, u64 size)
{
	exfat_set_entry_type((struct dentry_t *)ep, TYPE_STREAM);
	ep->flags = flags;
	SET32_A(ep->start_clu, start_clu);
	SET64_A(ep->valid_size, size);
	SET64_A(ep->size, size);
}