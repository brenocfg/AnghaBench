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
struct iio_demux_table {unsigned int from; unsigned int length; unsigned int to; int /*<<< orphan*/  l; } ;
struct iio_buffer {int /*<<< orphan*/  demux_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct iio_demux_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iio_buffer_add_demux(struct iio_buffer *buffer,
	struct iio_demux_table **p, unsigned int in_loc, unsigned int out_loc,
	unsigned int length)
{

	if (*p && (*p)->from + (*p)->length == in_loc &&
		(*p)->to + (*p)->length == out_loc) {
		(*p)->length += length;
	} else {
		*p = kmalloc(sizeof(**p), GFP_KERNEL);
		if (*p == NULL)
			return -ENOMEM;
		(*p)->from = in_loc;
		(*p)->to = out_loc;
		(*p)->length = length;
		list_add_tail(&(*p)->l, &buffer->demux_list);
	}

	return 0;
}