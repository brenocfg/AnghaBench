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
struct gb_operation_msg_hdr {scalar_t__* pad; } ;

/* Variables and functions */

__attribute__((used)) static void gb_message_cport_clear(struct gb_operation_msg_hdr *header)
{
	header->pad[0] = 0;
}