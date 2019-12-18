#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct TYPE_3__ {scalar_t__ imagesize; scalar_t__ packetsize; scalar_t__ num_packets; scalar_t__ packet_read_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_2__ packet_data_head ; 
 TYPE_1__ rbu_data ; 

__attribute__((used)) static void init_packet_head(void)
{
	INIT_LIST_HEAD(&packet_data_head.list);
	rbu_data.packet_read_count = 0;
	rbu_data.num_packets = 0;
	rbu_data.packetsize = 0;
	rbu_data.imagesize = 0;
}