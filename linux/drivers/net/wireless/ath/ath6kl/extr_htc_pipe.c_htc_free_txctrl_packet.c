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
struct htc_target {int dummy; } ;
struct htc_packet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_htc_txctrl_packet (struct htc_packet*) ; 

__attribute__((used)) static void htc_free_txctrl_packet(struct htc_target *target,
				   struct htc_packet *packet)
{
	destroy_htc_txctrl_packet(packet);
}