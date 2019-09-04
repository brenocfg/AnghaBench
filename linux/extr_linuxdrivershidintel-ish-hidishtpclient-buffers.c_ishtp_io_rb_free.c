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
struct TYPE_2__ {struct ishtp_cl_rb* data; } ;
struct ishtp_cl_rb {TYPE_1__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ishtp_cl_rb*) ; 

void ishtp_io_rb_free(struct ishtp_cl_rb *rb)
{
	if (rb == NULL)
		return;

	kfree(rb->buffer.data);
	kfree(rb);
}