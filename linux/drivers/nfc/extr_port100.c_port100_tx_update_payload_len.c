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
struct port100_frame {int /*<<< orphan*/  datalen; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port100_tx_update_payload_len(void *_frame, int len)
{
	struct port100_frame *frame = _frame;

	frame->datalen = cpu_to_le16(le16_to_cpu(frame->datalen) + len);
}