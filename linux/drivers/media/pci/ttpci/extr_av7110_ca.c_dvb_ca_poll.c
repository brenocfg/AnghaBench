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
struct file {struct dvb_device* private_data; } ;
struct dvb_ringbuffer {int /*<<< orphan*/  queue; } ;
struct dvb_device {struct av7110* priv; } ;
struct av7110 {struct dvb_ringbuffer ci_wbuffer; struct dvb_ringbuffer ci_rbuffer; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int /*<<< orphan*/  dvb_ringbuffer_empty (struct dvb_ringbuffer*) ; 
 int dvb_ringbuffer_free (struct dvb_ringbuffer*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t dvb_ca_poll (struct file *file, poll_table *wait)
{
	struct dvb_device *dvbdev = file->private_data;
	struct av7110 *av7110 = dvbdev->priv;
	struct dvb_ringbuffer *rbuf = &av7110->ci_rbuffer;
	struct dvb_ringbuffer *wbuf = &av7110->ci_wbuffer;
	__poll_t mask = 0;

	dprintk(8, "av7110:%p\n",av7110);

	poll_wait(file, &rbuf->queue, wait);
	poll_wait(file, &wbuf->queue, wait);

	if (!dvb_ringbuffer_empty(rbuf))
		mask |= (EPOLLIN | EPOLLRDNORM);

	if (dvb_ringbuffer_free(wbuf) > 1024)
		mask |= (EPOLLOUT | EPOLLWRNORM);

	return mask;
}