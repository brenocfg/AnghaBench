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
struct usbip_header_ret_unlink {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  be32_to_cpus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32s (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void correct_endian_ret_unlink(struct usbip_header_ret_unlink *pdu,
				      int send)
{
	if (send)
		cpu_to_be32s(&pdu->status);
	else
		be32_to_cpus(&pdu->status);
}