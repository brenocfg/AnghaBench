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
typedef  int u8 ;
typedef  int u32 ;
struct rvt_qpn_table {unsigned int flags; int last; int incr; int nmaps; struct rvt_qpn_map* map; int /*<<< orphan*/  lock; } ;
struct rvt_qpn_map {int /*<<< orphan*/  page; } ;
struct TYPE_4__ {int qos_shift; } ;
struct TYPE_3__ {int (* alloc_qpn ) (struct rvt_dev_info*,struct rvt_qpn_table*,int,int) ;} ;
struct rvt_dev_info {TYPE_2__ dparms; TYPE_1__ driver_f; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int IB_QPT_GSI ; 
 int IB_QPT_SMI ; 
 int RVT_BITS_PER_PAGE ; 
 int RVT_BITS_PER_PAGE_MASK ; 
 int RVT_QPNMAP_ENTRIES ; 
 int RVT_QPN_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  get_map_page (struct rvt_qpn_table*,struct rvt_qpn_map*) ; 
 int mk_qpn (struct rvt_qpn_table*,struct rvt_qpn_map*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct rvt_dev_info*,struct rvt_qpn_table*,int,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int alloc_qpn(struct rvt_dev_info *rdi, struct rvt_qpn_table *qpt,
		     enum ib_qp_type type, u8 port_num)
{
	u32 i, offset, max_scan, qpn;
	struct rvt_qpn_map *map;
	u32 ret;

	if (rdi->driver_f.alloc_qpn)
		return rdi->driver_f.alloc_qpn(rdi, qpt, type, port_num);

	if (type == IB_QPT_SMI || type == IB_QPT_GSI) {
		unsigned n;

		ret = type == IB_QPT_GSI;
		n = 1 << (ret + 2 * (port_num - 1));
		spin_lock(&qpt->lock);
		if (qpt->flags & n)
			ret = -EINVAL;
		else
			qpt->flags |= n;
		spin_unlock(&qpt->lock);
		goto bail;
	}

	qpn = qpt->last + qpt->incr;
	if (qpn >= RVT_QPN_MAX)
		qpn = qpt->incr | ((qpt->last & 1) ^ 1);
	/* offset carries bit 0 */
	offset = qpn & RVT_BITS_PER_PAGE_MASK;
	map = &qpt->map[qpn / RVT_BITS_PER_PAGE];
	max_scan = qpt->nmaps - !offset;
	for (i = 0;;) {
		if (unlikely(!map->page)) {
			get_map_page(qpt, map);
			if (unlikely(!map->page))
				break;
		}
		do {
			if (!test_and_set_bit(offset, map->page)) {
				qpt->last = qpn;
				ret = qpn;
				goto bail;
			}
			offset += qpt->incr;
			/*
			 * This qpn might be bogus if offset >= BITS_PER_PAGE.
			 * That is OK.   It gets re-assigned below
			 */
			qpn = mk_qpn(qpt, map, offset);
		} while (offset < RVT_BITS_PER_PAGE && qpn < RVT_QPN_MAX);
		/*
		 * In order to keep the number of pages allocated to a
		 * minimum, we scan the all existing pages before increasing
		 * the size of the bitmap table.
		 */
		if (++i > max_scan) {
			if (qpt->nmaps == RVT_QPNMAP_ENTRIES)
				break;
			map = &qpt->map[qpt->nmaps++];
			/* start at incr with current bit 0 */
			offset = qpt->incr | (offset & 1);
		} else if (map < &qpt->map[qpt->nmaps]) {
			++map;
			/* start at incr with current bit 0 */
			offset = qpt->incr | (offset & 1);
		} else {
			map = &qpt->map[0];
			/* wrap to first map page, invert bit 0 */
			offset = qpt->incr | ((offset & 1) ^ 1);
		}
		/* there can be no set bits in low-order QoS bits */
		WARN_ON(rdi->dparms.qos_shift > 1 &&
			offset & ((BIT(rdi->dparms.qos_shift - 1) - 1) << 1));
		qpn = mk_qpn(qpt, map, offset);
	}

	ret = -ENOMEM;

bail:
	return ret;
}