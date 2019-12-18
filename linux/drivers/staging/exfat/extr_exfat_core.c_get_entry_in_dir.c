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
struct super_block {int dummy; } ;
struct dentry_t {int dummy; } ;
struct chain_t {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ FFS_SUCCESS ; 
 int /*<<< orphan*/ * buf_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_location (struct super_block*,struct chain_t*,int,int /*<<< orphan*/ *,int*) ; 

struct dentry_t *get_entry_in_dir(struct super_block *sb, struct chain_t *p_dir,
				  s32 entry, sector_t *sector)
{
	s32 off;
	sector_t sec;
	u8 *buf;

	if (find_location(sb, p_dir, entry, &sec, &off) != FFS_SUCCESS)
		return NULL;

	buf = buf_getblk(sb, sec);

	if (!buf)
		return NULL;

	if (sector)
		*sector = sec;
	return (struct dentry_t *)(buf + off);
}