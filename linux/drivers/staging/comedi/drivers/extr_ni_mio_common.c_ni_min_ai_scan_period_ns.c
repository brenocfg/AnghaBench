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
struct ni_private {scalar_t__ is_6143; scalar_t__ is_611x; } ;
struct ni_board_struct {unsigned int ai_speed; } ;
struct comedi_device {struct ni_private* private; struct ni_board_struct* board_ptr; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int ni_min_ai_scan_period_ns(struct comedi_device *dev,
					     unsigned int num_channels)
{
	const struct ni_board_struct *board = dev->board_ptr;
	struct ni_private *devpriv = dev->private;

	/* simultaneously-sampled inputs */
	if (devpriv->is_611x || devpriv->is_6143)
		return board->ai_speed;

	/* multiplexed inputs */
	return board->ai_speed * num_channels;
}