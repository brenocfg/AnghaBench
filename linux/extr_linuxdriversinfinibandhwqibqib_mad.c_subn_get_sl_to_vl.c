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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int port_cap_flags; } ;
struct qib_ibport {int* sl_to_vl; TYPE_1__ rvp; } ;
struct ib_smp {int /*<<< orphan*/  status; scalar_t__ data; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int IB_PORT_SL_MAP_SUP ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_METHOD ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int reply (struct ib_smp*) ; 
 struct qib_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subn_get_sl_to_vl(struct ib_smp *smp, struct ib_device *ibdev,
			     u8 port)
{
	struct qib_ibport *ibp = to_iport(ibdev, port);
	u8 *p = (u8 *) smp->data;
	unsigned i;

	memset(smp->data, 0, sizeof(smp->data));

	if (!(ibp->rvp.port_cap_flags & IB_PORT_SL_MAP_SUP))
		smp->status |= IB_SMP_UNSUP_METHOD;
	else
		for (i = 0; i < ARRAY_SIZE(ibp->sl_to_vl); i += 2)
			*p++ = (ibp->sl_to_vl[i] << 4) | ibp->sl_to_vl[i + 1];

	return reply(smp);
}