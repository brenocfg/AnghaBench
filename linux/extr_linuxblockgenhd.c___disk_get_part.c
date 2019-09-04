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
struct hd_struct {int len; int /*<<< orphan*/ * part; } ;
struct gendisk {int /*<<< orphan*/  part_tbl; } ;
struct disk_part_tbl {int len; int /*<<< orphan*/ * part; } ;

/* Variables and functions */
 struct hd_struct* rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct hd_struct *__disk_get_part(struct gendisk *disk, int partno)
{
	struct disk_part_tbl *ptbl = rcu_dereference(disk->part_tbl);

	if (unlikely(partno < 0 || partno >= ptbl->len))
		return NULL;
	return rcu_dereference(ptbl->part[partno]);
}