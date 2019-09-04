#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gendisk {struct amiga_floppy_struct* private_data; } ;
struct amiga_floppy_struct {int track; scalar_t__ dirty; } ;
struct TYPE_2__ {int pra; } ;

/* Variables and functions */
 int DISK_EVENT_MEDIA_CHANGE ; 
 int DSKCHANGE ; 
 TYPE_1__ ciaa ; 
 int /*<<< orphan*/  fd_deselect (int) ; 
 int /*<<< orphan*/  fd_probe (int) ; 
 int /*<<< orphan*/  fd_select (int) ; 
 int /*<<< orphan*/  get_fdc (int) ; 
 int /*<<< orphan*/  rel_fdc () ; 
 struct amiga_floppy_struct* unit ; 
 scalar_t__ writefromint ; 
 scalar_t__ writepending ; 

__attribute__((used)) static unsigned amiga_check_events(struct gendisk *disk, unsigned int clearing)
{
	struct amiga_floppy_struct *p = disk->private_data;
	int drive = p - unit;
	int changed;
	static int first_time = 1;

	if (first_time)
		changed = first_time--;
	else {
		get_fdc(drive);
		fd_select (drive);
		changed = !(ciaa.pra & DSKCHANGE);
		fd_deselect (drive);
		rel_fdc();
	}

	if (changed) {
		fd_probe(drive);
		p->track = -1;
		p->dirty = 0;
		writepending = 0; /* if this was true before, too bad! */
		writefromint = 0;
		return DISK_EVENT_MEDIA_CHANGE;
	}
	return 0;
}