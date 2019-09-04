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
struct ubi_wl_entry {int ec; } ;
struct ubi_device {int /*<<< orphan*/  wl_lock; struct ubi_wl_entry** lookuptbl; } ;
struct seq_file {struct ubi_device* private; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int ubi_io_is_bad (struct ubi_device*,int) ; 

__attribute__((used)) static int eraseblk_count_seq_show(struct seq_file *s, void *iter)
{
	struct ubi_device *ubi = s->private;
	struct ubi_wl_entry *wl;
	int *block_number = iter;
	int erase_count = -1;
	int err;

	/* If this is the start, print a header */
	if (iter == SEQ_START_TOKEN) {
		seq_puts(s,
			 "physical_block_number\terase_count\tblock_status\tread_status\n");
		return 0;
	}

	err = ubi_io_is_bad(ubi, *block_number);
	if (err)
		return err;

	spin_lock(&ubi->wl_lock);

	wl = ubi->lookuptbl[*block_number];
	if (wl)
		erase_count = wl->ec;

	spin_unlock(&ubi->wl_lock);

	if (erase_count < 0)
		return 0;

	seq_printf(s, "%-22d\t%-11d\n", *block_number, erase_count);

	return 0;
}