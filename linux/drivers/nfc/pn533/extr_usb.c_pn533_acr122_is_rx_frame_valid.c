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
struct TYPE_2__ {int type; int datalen; } ;
struct pn533_acr122_rx_frame {int* data; TYPE_1__ ccid; } ;
struct pn533 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static bool pn533_acr122_is_rx_frame_valid(void *_frame, struct pn533 *dev)
{
	struct pn533_acr122_rx_frame *frame = _frame;

	if (frame->ccid.type != 0x83)
		return false;

	if (!frame->ccid.datalen)
		return false;

	if (frame->data[frame->ccid.datalen - 2] == 0x63)
		return false;

	return true;
}