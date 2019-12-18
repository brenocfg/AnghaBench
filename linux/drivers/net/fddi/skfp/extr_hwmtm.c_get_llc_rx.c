#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* llc_rx_pipe; int /*<<< orphan*/  queued_rx_frames; } ;
struct TYPE_7__ {TYPE_1__ hwm; } ;
struct s_smc {TYPE_2__ os; } ;
struct TYPE_8__ {struct TYPE_8__* sm_next; } ;
typedef  TYPE_3__ SMbuf ;

/* Variables and functions */
 int /*<<< orphan*/  DB_GEN (int,char*,TYPE_3__*) ; 

__attribute__((used)) static SMbuf *get_llc_rx(struct s_smc *smc)
{
	SMbuf	*mb ;

	if ((mb = smc->os.hwm.llc_rx_pipe)) {
		smc->os.hwm.queued_rx_frames-- ;
		smc->os.hwm.llc_rx_pipe = mb->sm_next ;
	}
	DB_GEN(4, "get_llc_rx: mb = 0x%p", mb);
	return mb;
}