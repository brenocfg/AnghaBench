#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  doorbell_ack; } ;
struct bna_ib {scalar_t__ coalescing_timeo; TYPE_1__ door_bell; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_DOORBELL_IB_INT_ACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bna_ib_coalescing_timeo_set(struct bna_ib *ib, u8 coalescing_timeo)
{
	ib->coalescing_timeo = coalescing_timeo;
	ib->door_bell.doorbell_ack = BNA_DOORBELL_IB_INT_ACK(
				(u32)ib->coalescing_timeo, 0);
}