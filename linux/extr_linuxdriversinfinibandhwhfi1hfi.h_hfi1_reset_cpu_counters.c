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
struct TYPE_3__ {int /*<<< orphan*/  rc_qacks; void* z_rc_qacks; int /*<<< orphan*/  rc_acks; void* z_rc_acks; } ;
struct TYPE_4__ {TYPE_1__ rvp; } ;
struct hfi1_pportdata {TYPE_2__ ibport_data; } ;
struct hfi1_devdata {int num_pports; int /*<<< orphan*/  send_schedule; void* z_send_schedule; int /*<<< orphan*/  rcv_limit; void* z_rcv_limit; int /*<<< orphan*/  int_counter; void* z_int_counter; } ;

/* Variables and functions */
 void* get_all_cpu_total (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hfi1_reset_cpu_counters(struct hfi1_devdata *dd)
{
	struct hfi1_pportdata *ppd;
	int i;

	dd->z_int_counter = get_all_cpu_total(dd->int_counter);
	dd->z_rcv_limit = get_all_cpu_total(dd->rcv_limit);
	dd->z_send_schedule = get_all_cpu_total(dd->send_schedule);

	ppd = (struct hfi1_pportdata *)(dd + 1);
	for (i = 0; i < dd->num_pports; i++, ppd++) {
		ppd->ibport_data.rvp.z_rc_acks =
			get_all_cpu_total(ppd->ibport_data.rvp.rc_acks);
		ppd->ibport_data.rvp.z_rc_qacks =
			get_all_cpu_total(ppd->ibport_data.rvp.rc_qacks);
	}
}