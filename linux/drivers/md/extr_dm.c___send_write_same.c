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
struct clone_info {int dummy; } ;

/* Variables and functions */
 int __send_changing_extent_only (struct clone_info*,struct dm_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_num_write_same_bios (struct dm_target*) ; 

__attribute__((used)) static int __send_write_same(struct clone_info *ci, struct dm_target *ti)
{
	return __send_changing_extent_only(ci, ti, get_num_write_same_bios(ti));
}