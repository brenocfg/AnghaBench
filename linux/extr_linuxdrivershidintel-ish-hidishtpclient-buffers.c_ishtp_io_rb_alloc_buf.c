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
struct TYPE_2__ {size_t size; int /*<<< orphan*/  data; } ;
struct ishtp_cl_rb {TYPE_1__ buffer; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmalloc (size_t,int /*<<< orphan*/ ) ; 

int ishtp_io_rb_alloc_buf(struct ishtp_cl_rb *rb, size_t length)
{
	if (!rb)
		return -EINVAL;

	if (length == 0)
		return 0;

	rb->buffer.data = kmalloc(length, GFP_KERNEL);
	if (!rb->buffer.data)
		return -ENOMEM;

	rb->buffer.size = length;
	return 0;
}