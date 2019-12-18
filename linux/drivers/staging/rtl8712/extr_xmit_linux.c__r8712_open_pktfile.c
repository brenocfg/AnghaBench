#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pkt_file {int /*<<< orphan*/  buf_start; int /*<<< orphan*/  cur_buffer; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  pkt_len; int /*<<< orphan*/  cur_addr; TYPE_1__* pkt; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ _pkt ;

/* Variables and functions */

void _r8712_open_pktfile(_pkt *pktptr, struct pkt_file *pfile)
{
	pfile->pkt = pktptr;
	pfile->cur_addr = pfile->buf_start = pktptr->data;
	pfile->pkt_len = pfile->buf_len = pktptr->len;
	pfile->cur_buffer = pfile->buf_start;
}