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
struct rpd {int nseg; TYPE_1__* rsd; } ;
struct host_bsq {int /*<<< orphan*/  freebuf_count; struct buffer* freebuf; } ;
struct fore200e {struct host_bsq** host_bsq; } ;
struct buffer {size_t scheme; size_t magn; struct buffer* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 struct buffer* FORE200E_HDL2BUF (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fore200e_collect_rpd(struct fore200e* fore200e, struct rpd* rpd)
{
    struct host_bsq* bsq;
    struct buffer*   buffer;
    int              i;
    
    for (i = 0; i < rpd->nseg; i++) {

	/* rebuild rx buffer address from rsd handle */
	buffer = FORE200E_HDL2BUF(rpd->rsd[ i ].handle);

	bsq = &fore200e->host_bsq[ buffer->scheme ][ buffer->magn ];

#ifdef FORE200E_BSQ_DEBUG
	bsq_audit(2, bsq, buffer->scheme, buffer->magn);

	if (buffer->supplied == 0)
	    printk(FORE200E "queue %d.%d, buffer %ld was not supplied\n",
		   buffer->scheme, buffer->magn, buffer->index);
	buffer->supplied = 0;
#endif

	/* re-insert the buffer into the free buffer list */
	buffer->next = bsq->freebuf;
	bsq->freebuf = buffer;

	/* then increment the number of free rx buffers */
	bsq->freebuf_count++;
    }
}