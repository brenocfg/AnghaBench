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
struct dvb_ringbuffer {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ci_ll_release(struct dvb_ringbuffer *cirbuf, struct dvb_ringbuffer *ciwbuf)
{
	vfree(cirbuf->data);
	cirbuf->data = NULL;
	vfree(ciwbuf->data);
	ciwbuf->data = NULL;
}