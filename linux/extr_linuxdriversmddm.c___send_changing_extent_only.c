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
struct dm_target {int dummy; } ;
struct clone_info {unsigned int sector; scalar_t__ sector_count; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  (* is_split_required_fn ) (struct dm_target*) ;
typedef  unsigned int (* get_num_bios_fn ) (struct dm_target*) ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  __send_duplicate_bios (struct clone_info*,struct dm_target*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  max_io_len (unsigned int,struct dm_target*) ; 
 int /*<<< orphan*/  max_io_len_target_boundary (unsigned int,struct dm_target*) ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __send_changing_extent_only(struct clone_info *ci, struct dm_target *ti,
				       get_num_bios_fn get_num_bios,
				       is_split_required_fn is_split_required)
{
	unsigned len;
	unsigned num_bios;

	/*
	 * Even though the device advertised support for this type of
	 * request, that does not mean every target supports it, and
	 * reconfiguration might also have changed that since the
	 * check was performed.
	 */
	num_bios = get_num_bios ? get_num_bios(ti) : 0;
	if (!num_bios)
		return -EOPNOTSUPP;

	if (is_split_required && !is_split_required(ti))
		len = min((sector_t)ci->sector_count, max_io_len_target_boundary(ci->sector, ti));
	else
		len = min((sector_t)ci->sector_count, max_io_len(ci->sector, ti));

	__send_duplicate_bios(ci, ti, num_bios, &len);

	ci->sector += len;
	ci->sector_count -= len;

	return 0;
}