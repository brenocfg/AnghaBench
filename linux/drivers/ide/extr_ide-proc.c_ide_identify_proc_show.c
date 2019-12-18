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
typedef  char u8 ;
struct seq_file {scalar_t__ private; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 scalar_t__ taskfile_lib_get_identify (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ide_identify_proc_show(struct seq_file *m, void *v)
{
	ide_drive_t *drive = (ide_drive_t *)m->private;
	u8 *buf;

	if (!drive) {
		seq_putc(m, '\n');
		return 0;
	}

	buf = kmalloc(SECTOR_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	if (taskfile_lib_get_identify(drive, buf) == 0) {
		__le16 *val = (__le16 *)buf;
		int i;

		for (i = 0; i < SECTOR_SIZE / 2; i++) {
			seq_printf(m, "%04x%c", le16_to_cpu(val[i]),
					(i % 8) == 7 ? '\n' : ' ');
		}
	} else
		seq_putc(m, buf[0]);
	kfree(buf);
	return 0;
}