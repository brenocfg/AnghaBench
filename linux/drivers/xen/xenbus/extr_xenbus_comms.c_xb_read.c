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
struct xenstore_domain_interface {scalar_t__ rsp_cons; scalar_t__ rsp_prod; int /*<<< orphan*/  rsp; } ;
typedef  scalar_t__ XENSTORE_RING_IDX ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ XENSTORE_RING_SIZE ; 
 int /*<<< orphan*/  check_indexes (scalar_t__,scalar_t__) ; 
 char* get_input_chunk (scalar_t__,scalar_t__,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  memcpy (void*,char const*,unsigned int) ; 
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_mb () ; 
 int /*<<< orphan*/  virt_rmb () ; 
 int /*<<< orphan*/  xen_store_evtchn ; 
 struct xenstore_domain_interface* xen_store_interface ; 

__attribute__((used)) static int xb_read(void *data, unsigned int len)
{
	struct xenstore_domain_interface *intf = xen_store_interface;
	XENSTORE_RING_IDX cons, prod;
	unsigned int bytes = 0;

	while (len != 0) {
		unsigned int avail;
		const char *src;

		/* Read indexes, then verify. */
		cons = intf->rsp_cons;
		prod = intf->rsp_prod;
		if (cons == prod)
			return bytes;

		if (!check_indexes(cons, prod)) {
			intf->rsp_cons = intf->rsp_prod = 0;
			return -EIO;
		}

		src = get_input_chunk(cons, prod, intf->rsp, &avail);
		if (avail == 0)
			continue;
		if (avail > len)
			avail = len;

		/* Must read data /after/ reading the producer index. */
		virt_rmb();

		memcpy(data, src, avail);
		data += avail;
		len -= avail;
		bytes += avail;

		/* Other side must not see free space until we've copied out */
		virt_mb();
		intf->rsp_cons += avail;

		/* Implies mb(): other side will see the updated consumer. */
		if (intf->rsp_prod - cons >= XENSTORE_RING_SIZE)
			notify_remote_via_evtchn(xen_store_evtchn);
	}

	return bytes;
}