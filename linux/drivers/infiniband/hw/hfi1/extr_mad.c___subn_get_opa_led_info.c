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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct opa_led_info {int /*<<< orphan*/  rsvd_led_mask; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int /*<<< orphan*/  led_override_timer_active; } ;
struct hfi1_devdata {struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_AM_NPORT (int) ; 
 int OPA_LED_SHIFT ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct hfi1_devdata* dd_from_ibdev (struct ib_device*) ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ smp_length_check (int,int) ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static int __subn_get_opa_led_info(struct opa_smp *smp, u32 am, u8 *data,
				   struct ib_device *ibdev, u8 port,
				   u32 *resp_len, u32 max_len)
{
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	struct hfi1_pportdata *ppd = dd->pport;
	struct opa_led_info *p = (struct opa_led_info *)data;
	u32 nport = OPA_AM_NPORT(am);
	u32 is_beaconing_active;

	if (nport != 1 || smp_length_check(sizeof(*p), max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	/*
	 * This pairs with the memory barrier in hfi1_start_led_override to
	 * ensure that we read the correct state of LED beaconing represented
	 * by led_override_timer_active
	 */
	smp_rmb();
	is_beaconing_active = !!atomic_read(&ppd->led_override_timer_active);
	p->rsvd_led_mask = cpu_to_be32(is_beaconing_active << OPA_LED_SHIFT);

	if (resp_len)
		*resp_len += sizeof(struct opa_led_info);

	return reply((struct ib_mad_hdr *)smp);
}