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
struct isowbuf_t {unsigned char idle; scalar_t__ data; scalar_t__ wbits; int /*<<< orphan*/  writesem; scalar_t__ write; scalar_t__ nextread; scalar_t__ read; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAS_OUTBUFPAD ; 
 scalar_t__ BAS_OUTBUFSIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,unsigned char,int /*<<< orphan*/ ) ; 

void gigaset_isowbuf_init(struct isowbuf_t *iwb, unsigned char idle)
{
	iwb->read = 0;
	iwb->nextread = 0;
	iwb->write = 0;
	atomic_set(&iwb->writesem, 1);
	iwb->wbits = 0;
	iwb->idle = idle;
	memset(iwb->data + BAS_OUTBUFSIZE, idle, BAS_OUTBUFPAD);
}