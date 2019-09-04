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
struct gru_control_block_status {scalar_t__ istatus; } ;
struct control_block_extended_exc_detail {int opc; int exopc; int ecause; int /*<<< orphan*/  exceptdet1; int /*<<< orphan*/  exceptdet0; } ;

/* Variables and functions */
 scalar_t__ CBS_EXCEPTION ; 
 int /*<<< orphan*/  gru_get_cb_exception_detail (void*,struct control_block_extended_exc_detail*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static char *gru_get_cb_exception_detail_str(int ret, void *cb,
					     char *buf, int size)
{
	struct gru_control_block_status *gen = (void *)cb;
	struct control_block_extended_exc_detail excdet;

	if (ret > 0 && gen->istatus == CBS_EXCEPTION) {
		gru_get_cb_exception_detail(cb, &excdet);
		snprintf(buf, size,
			"GRU:%d exception: cb %p, opc %d, exopc %d, ecause 0x%x,"
			"excdet0 0x%lx, excdet1 0x%x", smp_processor_id(),
			gen, excdet.opc, excdet.exopc, excdet.ecause,
			excdet.exceptdet0, excdet.exceptdet1);
	} else {
		snprintf(buf, size, "No exception");
	}
	return buf;
}