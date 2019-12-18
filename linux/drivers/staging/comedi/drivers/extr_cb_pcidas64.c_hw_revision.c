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
typedef  int u16 ;
struct pcidas64_board {scalar_t__ layout; } ;
struct comedi_device {struct pcidas64_board* board_ptr; } ;

/* Variables and functions */
 scalar_t__ LAYOUT_4020 ; 

__attribute__((used)) static unsigned int hw_revision(const struct comedi_device *dev,
				u16 hw_status_bits)
{
	const struct pcidas64_board *board = dev->board_ptr;

	if (board->layout == LAYOUT_4020)
		return (hw_status_bits >> 13) & 0x7;

	return (hw_status_bits >> 12) & 0xf;
}