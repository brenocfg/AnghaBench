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
struct pvcalls_data_intf {int in_cons; int in_prod; scalar_t__ in_error; } ;
struct pvcalls_data {int in; } ;
struct iov_iter {int dummy; } ;
typedef  scalar_t__ int32_t ;
typedef  int RING_IDX ;

/* Variables and functions */
 int MSG_PEEK ; 
 int /*<<< orphan*/  PVCALLS_RING_ORDER ; 
 int XEN_FLEX_RING_SIZE (int /*<<< orphan*/ ) ; 
 int copy_to_iter (int,size_t,struct iov_iter*) ; 
 int pvcalls_mask (int,int) ; 
 int pvcalls_queued (int,int,int) ; 
 int /*<<< orphan*/  virt_mb () ; 
 int /*<<< orphan*/  virt_rmb () ; 

__attribute__((used)) static int __read_ring(struct pvcalls_data_intf *intf,
		       struct pvcalls_data *data,
		       struct iov_iter *msg_iter,
		       size_t len, int flags)
{
	RING_IDX cons, prod, size, masked_prod, masked_cons;
	RING_IDX array_size = XEN_FLEX_RING_SIZE(PVCALLS_RING_ORDER);
	int32_t error;

	cons = intf->in_cons;
	prod = intf->in_prod;
	error = intf->in_error;
	/* get pointers before reading from the ring */
	virt_rmb();

	size = pvcalls_queued(prod, cons, array_size);
	masked_prod = pvcalls_mask(prod, array_size);
	masked_cons = pvcalls_mask(cons, array_size);

	if (size == 0)
		return error ?: size;

	if (len > size)
		len = size;

	if (masked_prod > masked_cons) {
		len = copy_to_iter(data->in + masked_cons, len, msg_iter);
	} else {
		if (len > (array_size - masked_cons)) {
			int ret = copy_to_iter(data->in + masked_cons,
				     array_size - masked_cons, msg_iter);
			if (ret != array_size - masked_cons) {
				len = ret;
				goto out;
			}
			len = ret + copy_to_iter(data->in, len - ret, msg_iter);
		} else {
			len = copy_to_iter(data->in + masked_cons, len, msg_iter);
		}
	}
out:
	/* read data from the ring before increasing the index */
	virt_mb();
	if (!(flags & MSG_PEEK))
		intf->in_cons += len;

	return len;
}