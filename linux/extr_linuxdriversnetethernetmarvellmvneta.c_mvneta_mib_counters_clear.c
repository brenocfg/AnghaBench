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
typedef  int /*<<< orphan*/  u32 ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ MVNETA_MIB_COUNTERS_BASE ; 
 int MVNETA_MIB_LATE_COLLISION ; 
 scalar_t__ MVNETA_OVERRUN_FRAME_COUNT ; 
 scalar_t__ MVNETA_RX_DISCARD_FRAME_COUNT ; 
 int /*<<< orphan*/  mvreg_read (struct mvneta_port*,scalar_t__) ; 

__attribute__((used)) static void mvneta_mib_counters_clear(struct mvneta_port *pp)
{
	int i;
	u32 dummy;

	/* Perform dummy reads from MIB counters */
	for (i = 0; i < MVNETA_MIB_LATE_COLLISION; i += 4)
		dummy = mvreg_read(pp, (MVNETA_MIB_COUNTERS_BASE + i));
	dummy = mvreg_read(pp, MVNETA_RX_DISCARD_FRAME_COUNT);
	dummy = mvreg_read(pp, MVNETA_OVERRUN_FRAME_COUNT);
}