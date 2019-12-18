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
struct ni_660x_private {int /*<<< orphan*/ ** ring; } ;
struct ni_660x_board {unsigned int n_chips; } ;
struct comedi_device {struct ni_660x_private* private; struct ni_660x_board* board_ptr; } ;

/* Variables and functions */
 unsigned int NI660X_COUNTERS_PER_CHIP ; 
 int /*<<< orphan*/  mite_free_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_660x_free_mite_rings(struct comedi_device *dev)
{
	const struct ni_660x_board *board = dev->board_ptr;
	struct ni_660x_private *devpriv = dev->private;
	unsigned int i;
	unsigned int j;

	for (i = 0; i < board->n_chips; ++i) {
		for (j = 0; j < NI660X_COUNTERS_PER_CHIP; ++j)
			mite_free_ring(devpriv->ring[i][j]);
	}
}