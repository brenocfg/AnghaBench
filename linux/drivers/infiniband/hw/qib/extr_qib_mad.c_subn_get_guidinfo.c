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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct qib_ibport {scalar_t__* guids; } ;
struct qib_pportdata {scalar_t__ guid; struct qib_ibport ibport_data; } ;
struct qib_devdata {unsigned int num_pports; struct qib_pportdata* pport; } ;
struct ib_smp {int /*<<< orphan*/  status; scalar_t__ data; int /*<<< orphan*/  attr_mod; } ;
struct ib_device {int dummy; } ;
typedef  scalar_t__ __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 unsigned int QIB_GUIDS_PER_PORT ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct qib_devdata* dd_from_ibdev (struct ib_device*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int reply (struct ib_smp*) ; 

__attribute__((used)) static int subn_get_guidinfo(struct ib_smp *smp, struct ib_device *ibdev,
			     u8 port)
{
	struct qib_devdata *dd = dd_from_ibdev(ibdev);
	u32 startgx = 8 * be32_to_cpu(smp->attr_mod);
	__be64 *p = (__be64 *) smp->data;
	unsigned pidx = port - 1; /* IB number port from 1, hdw from 0 */

	/* 32 blocks of 8 64-bit GUIDs per block */

	memset(smp->data, 0, sizeof(smp->data));

	if (startgx == 0 && pidx < dd->num_pports) {
		struct qib_pportdata *ppd = dd->pport + pidx;
		struct qib_ibport *ibp = &ppd->ibport_data;
		__be64 g = ppd->guid;
		unsigned i;

		/* GUID 0 is illegal */
		if (g == 0)
			smp->status |= IB_SMP_INVALID_FIELD;
		else {
			/* The first is a copy of the read-only HW GUID. */
			p[0] = g;
			for (i = 1; i < QIB_GUIDS_PER_PORT; i++)
				p[i] = ibp->guids[i - 1];
		}
	} else
		smp->status |= IB_SMP_INVALID_FIELD;

	return reply(smp);
}