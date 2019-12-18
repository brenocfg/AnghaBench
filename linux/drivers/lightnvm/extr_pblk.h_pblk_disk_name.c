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
struct pblk {struct gendisk* disk; } ;
struct gendisk {char* disk_name; } ;

/* Variables and functions */

__attribute__((used)) static inline char *pblk_disk_name(struct pblk *pblk)
{
	struct gendisk *disk = pblk->disk;

	return disk->disk_name;
}