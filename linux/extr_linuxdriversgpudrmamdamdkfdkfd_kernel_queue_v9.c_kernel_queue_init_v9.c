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
struct kernel_queue_ops {int /*<<< orphan*/  submit_packet; int /*<<< orphan*/  uninitialize; int /*<<< orphan*/  initialize; } ;

/* Variables and functions */
 int /*<<< orphan*/  initialize_v9 ; 
 int /*<<< orphan*/  submit_packet_v9 ; 
 int /*<<< orphan*/  uninitialize_v9 ; 

void kernel_queue_init_v9(struct kernel_queue_ops *ops)
{
	ops->initialize = initialize_v9;
	ops->uninitialize = uninitialize_v9;
	ops->submit_packet = submit_packet_v9;
}