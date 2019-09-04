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
typedef  size_t u32 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_ibport {int /*<<< orphan*/ * sc_to_sl; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ smp_length_check (size_t,size_t) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __subn_get_opa_sc_to_sl(struct opa_smp *smp, u32 am, u8 *data,
				   struct ib_device *ibdev, u8 port,
				   u32 *resp_len, u32 max_len)
{
	struct hfi1_ibport *ibp = to_iport(ibdev, port);
	u8 *p = data;
	size_t size = ARRAY_SIZE(ibp->sc_to_sl); /* == 32 */
	unsigned i;

	if (am || smp_length_check(size, max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	for (i = 0; i < ARRAY_SIZE(ibp->sc_to_sl); i++)
		*p++ = ibp->sc_to_sl[i];

	if (resp_len)
		*resp_len += size;

	return reply((struct ib_mad_hdr *)smp);
}