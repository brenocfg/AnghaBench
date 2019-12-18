#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcidas64_board {scalar_t__ layout; } ;
struct comedi_device {TYPE_2__* read_subdev; struct pcidas64_board* board_ptr; } ;
struct TYPE_4__ {TYPE_1__* async; int /*<<< orphan*/  busy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 scalar_t__ LAYOUT_4020 ; 
 scalar_t__ use_internal_queue_6xxx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int external_ai_queue_in_use(struct comedi_device *dev)
{
	const struct pcidas64_board *board = dev->board_ptr;

	if (!dev->read_subdev->busy)
		return 0;
	if (board->layout == LAYOUT_4020)
		return 0;
	else if (use_internal_queue_6xxx(&dev->read_subdev->async->cmd))
		return 0;
	return 1;
}