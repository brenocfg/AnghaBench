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
struct srp_target_port {scalar_t__ using_rdma_cm; } ;
struct srp_rdma_ch {struct srp_target_port* target; } ;

/* Variables and functions */
 int srp_ib_lookup_path (struct srp_rdma_ch*) ; 
 int srp_rdma_lookup_path (struct srp_rdma_ch*) ; 

__attribute__((used)) static int srp_lookup_path(struct srp_rdma_ch *ch)
{
	struct srp_target_port *target = ch->target;

	return target->using_rdma_cm ? srp_rdma_lookup_path(ch) :
		srp_ib_lookup_path(ch);
}