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
typedef  scalar_t__ u8 ;
struct port100_frame {scalar_t__ start_frame; scalar_t__ extended_frame; scalar_t__ datalen_checksum; int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ PORT100_FRAME_CHECKSUM (struct port100_frame*) ; 
 int /*<<< orphan*/  PORT100_FRAME_EXT ; 
 int /*<<< orphan*/  PORT100_FRAME_SOF ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ port100_checksum (int /*<<< orphan*/ ) ; 
 scalar_t__ port100_data_checksum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool port100_rx_frame_is_valid(void *_frame)
{
	u8 checksum;
	struct port100_frame *frame = _frame;

	if (frame->start_frame != cpu_to_be16(PORT100_FRAME_SOF) ||
	    frame->extended_frame != cpu_to_be16(PORT100_FRAME_EXT))
		return false;

	checksum = port100_checksum(le16_to_cpu(frame->datalen));
	if (checksum != frame->datalen_checksum)
		return false;

	checksum = port100_data_checksum(frame->data,
					 le16_to_cpu(frame->datalen));
	if (checksum != PORT100_FRAME_CHECKSUM(frame))
		return false;

	return true;
}