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
struct hfi1_devdata {int /*<<< orphan*/  pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_AM_NPORT (int) ; 
 int OPA_LED_MASK ; 
 int __subn_get_opa_led_info (struct opa_smp*,int,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int*,int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct hfi1_devdata* dd_from_ibdev (struct ib_device*) ; 
 int /*<<< orphan*/  hfi1_start_led_override (int /*<<< orphan*/ ,int,int) ; 
 int reply (struct ib_mad_hdr*) ; 
 int /*<<< orphan*/  shutdown_led_override (int /*<<< orphan*/ ) ; 
 scalar_t__ smp_length_check (int,int) ; 

__attribute__((used)) static int __subn_set_opa_led_info(struct opa_smp *smp, u32 am, u8 *data,
				   struct ib_device *ibdev, u8 port,
				   u32 *resp_len, u32 max_len)
{
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	struct opa_led_info *p = (struct opa_led_info *)data;
	u32 nport = OPA_AM_NPORT(am);
	int on = !!(be32_to_cpu(p->rsvd_led_mask) & OPA_LED_MASK);

	if (nport != 1 || smp_length_check(sizeof(*p), max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	if (on)
		hfi1_start_led_override(dd->pport, 2000, 1500);
	else
		shutdown_led_override(dd->pport);

	return __subn_get_opa_led_info(smp, am, data, ibdev, port, resp_len,
				       max_len);
}