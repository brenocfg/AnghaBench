#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ idetape_tape_t ;
struct TYPE_6__ {TYPE_1__* driver_data; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_IDETAPE_WRITE ; 
 int /*<<< orphan*/  idetape_queue_rw_tail (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void idetape_pad_zeros(ide_drive_t *drive, int bcount)
{
	idetape_tape_t *tape = drive->driver_data;

	memset(tape->buf, 0, tape->buffer_size);

	while (bcount) {
		unsigned int count = min(tape->buffer_size, bcount);

		idetape_queue_rw_tail(drive, REQ_IDETAPE_WRITE, count);
		bcount -= count;
	}
}