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
struct gendisk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_get_integrity (struct gendisk*) ; 

__attribute__((used)) static bool integrity_profile_exists(struct gendisk *disk)
{
	return !!blk_get_integrity(disk);
}