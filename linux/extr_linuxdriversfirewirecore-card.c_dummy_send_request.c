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
struct fw_packet {int /*<<< orphan*/  (* callback ) (struct fw_packet*,struct fw_card*,int /*<<< orphan*/ ) ;} ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCODE_CANCELLED ; 
 int /*<<< orphan*/  stub1 (struct fw_packet*,struct fw_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dummy_send_request(struct fw_card *card, struct fw_packet *packet)
{
	packet->callback(packet, card, RCODE_CANCELLED);
}