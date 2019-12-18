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
struct socket {int dummy; } ;
struct siw_sge {unsigned int laddr; scalar_t__ length; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int PAGE_ALIGN (int) ; 
 unsigned int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int min (scalar_t__,unsigned int) ; 
 int siw_tcp_sendpages (struct socket*,struct page**,unsigned int,int) ; 

__attribute__((used)) static int siw_0copy_tx(struct socket *s, struct page **page,
			struct siw_sge *sge, unsigned int offset,
			unsigned int size)
{
	int i = 0, sent = 0, rv;
	int sge_bytes = min(sge->length - offset, size);

	offset = (sge->laddr + offset) & ~PAGE_MASK;

	while (sent != size) {
		rv = siw_tcp_sendpages(s, &page[i], offset, sge_bytes);
		if (rv >= 0) {
			sent += rv;
			if (size == sent || sge_bytes > rv)
				break;

			i += PAGE_ALIGN(sge_bytes + offset) >> PAGE_SHIFT;
			sge++;
			sge_bytes = min(sge->length, size - sent);
			offset = sge->laddr & ~PAGE_MASK;
		} else {
			sent = rv;
			break;
		}
	}
	return sent;
}