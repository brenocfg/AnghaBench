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
struct xenstore_domain_interface {scalar_t__ req_cons; scalar_t__ req_prod; int /*<<< orphan*/  req; } ;
typedef  scalar_t__ XENSTORE_RING_IDX ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  check_indexes (scalar_t__,scalar_t__) ; 
 void* get_output_chunk (scalar_t__,scalar_t__,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_mb () ; 
 int /*<<< orphan*/  virt_wmb () ; 
 int /*<<< orphan*/  xb_data_to_write () ; 
 int /*<<< orphan*/  xen_store_evtchn ; 
 struct xenstore_domain_interface* xen_store_interface ; 

__attribute__((used)) static int xb_write(const void *data, unsigned int len)
{
	struct xenstore_domain_interface *intf = xen_store_interface;
	XENSTORE_RING_IDX cons, prod;
	unsigned int bytes = 0;

	while (len != 0) {
		void *dst;
		unsigned int avail;

		/* Read indexes, then verify. */
		cons = intf->req_cons;
		prod = intf->req_prod;
		if (!check_indexes(cons, prod)) {
			intf->req_cons = intf->req_prod = 0;
			return -EIO;
		}
		if (!xb_data_to_write())
			return bytes;

		/* Must write data /after/ reading the consumer index. */
		virt_mb();

		dst = get_output_chunk(cons, prod, intf->req, &avail);
		if (avail == 0)
			continue;
		if (avail > len)
			avail = len;

		memcpy(dst, data, avail);
		data += avail;
		len -= avail;
		bytes += avail;

		/* Other side must not see new producer until data is there. */
		virt_wmb();
		intf->req_prod += avail;

		/* Implies mb(): other side will see the updated producer. */
		if (prod <= intf->req_cons)
			notify_remote_via_evtchn(xen_store_evtchn);
	}

	return bytes;
}