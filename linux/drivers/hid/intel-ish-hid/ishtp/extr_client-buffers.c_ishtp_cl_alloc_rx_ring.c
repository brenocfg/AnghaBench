#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ishtp_cl_rb {int /*<<< orphan*/  list; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct ishtp_cl {int rx_ring_size; TYPE_2__* device; int /*<<< orphan*/  free_list_spinlock; TYPE_1__ free_rb_list; } ;
struct TYPE_7__ {size_t max_msg_length; } ;
struct TYPE_8__ {TYPE_3__ props; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; TYPE_4__* fw_client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ishtp_cl_free_rx_ring (struct ishtp_cl*) ; 
 int ishtp_io_rb_alloc_buf (struct ishtp_cl_rb*,size_t) ; 
 struct ishtp_cl_rb* ishtp_io_rb_init (struct ishtp_cl*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ishtp_cl_alloc_rx_ring(struct ishtp_cl *cl)
{
	size_t	len = cl->device->fw_client->props.max_msg_length;
	int	j;
	struct ishtp_cl_rb *rb;
	int	ret = 0;
	unsigned long	flags;

	for (j = 0; j < cl->rx_ring_size; ++j) {
		rb = ishtp_io_rb_init(cl);
		if (!rb) {
			ret = -ENOMEM;
			goto out;
		}
		ret = ishtp_io_rb_alloc_buf(rb, len);
		if (ret)
			goto out;
		spin_lock_irqsave(&cl->free_list_spinlock, flags);
		list_add_tail(&rb->list, &cl->free_rb_list.list);
		spin_unlock_irqrestore(&cl->free_list_spinlock, flags);
	}

	return	0;

out:
	dev_err(&cl->device->dev, "error in allocating Rx buffers\n");
	ishtp_cl_free_rx_ring(cl);
	return	ret;
}