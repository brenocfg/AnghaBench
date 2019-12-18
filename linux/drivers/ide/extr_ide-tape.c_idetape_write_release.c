#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int blk_size; int user_bs_factor; int /*<<< orphan*/ * buf; int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_1__ idetape_tape_t ;
struct TYPE_9__ {TYPE_1__* driver_data; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ide_tape_flush_merge_buffer (TYPE_2__*) ; 
 int /*<<< orphan*/  idetape_flush_tape_buffers (TYPE_2__*) ; 
 int /*<<< orphan*/  idetape_pad_zeros (TYPE_2__*,int) ; 
 int /*<<< orphan*/  idetape_write_filemark (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idetape_write_release(ide_drive_t *drive, unsigned int minor)
{
	idetape_tape_t *tape = drive->driver_data;

	ide_tape_flush_merge_buffer(drive);
	tape->buf = kmalloc(tape->buffer_size, GFP_KERNEL);
	if (tape->buf != NULL) {
		idetape_pad_zeros(drive, tape->blk_size *
				(tape->user_bs_factor - 1));
		kfree(tape->buf);
		tape->buf = NULL;
	}
	idetape_write_filemark(drive);
	idetape_flush_tape_buffers(drive);
	idetape_flush_tape_buffers(drive);
}