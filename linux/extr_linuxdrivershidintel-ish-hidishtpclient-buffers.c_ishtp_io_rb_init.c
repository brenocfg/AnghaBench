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
struct ishtp_cl_rb {scalar_t__ buf_idx; struct ishtp_cl* cl; int /*<<< orphan*/  list; } ;
struct ishtp_cl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ishtp_cl_rb* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ishtp_cl_rb *ishtp_io_rb_init(struct ishtp_cl *cl)
{
	struct ishtp_cl_rb *rb;

	rb = kzalloc(sizeof(struct ishtp_cl_rb), GFP_KERNEL);
	if (!rb)
		return NULL;

	INIT_LIST_HEAD(&rb->list);
	rb->cl = cl;
	rb->buf_idx = 0;
	return rb;
}