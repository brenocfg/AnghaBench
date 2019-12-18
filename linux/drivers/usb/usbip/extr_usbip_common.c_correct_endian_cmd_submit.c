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
struct usbip_header_cmd_submit {int /*<<< orphan*/  interval; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32s (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void correct_endian_cmd_submit(struct usbip_header_cmd_submit *pdu,
				      int send)
{
	if (send) {
		pdu->transfer_flags = cpu_to_be32(pdu->transfer_flags);

		cpu_to_be32s(&pdu->transfer_buffer_length);
		cpu_to_be32s(&pdu->start_frame);
		cpu_to_be32s(&pdu->number_of_packets);
		cpu_to_be32s(&pdu->interval);
	} else {
		pdu->transfer_flags = be32_to_cpu(pdu->transfer_flags);

		be32_to_cpus(&pdu->transfer_buffer_length);
		be32_to_cpus(&pdu->start_frame);
		be32_to_cpus(&pdu->number_of_packets);
		be32_to_cpus(&pdu->interval);
	}
}