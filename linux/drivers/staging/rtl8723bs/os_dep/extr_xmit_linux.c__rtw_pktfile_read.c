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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
struct pkt_file {scalar_t__ buf_len; scalar_t__ pkt_len; int /*<<< orphan*/  cur_addr; int /*<<< orphan*/  pkt; } ;

/* Variables and functions */
 scalar_t__ rtw_remainder_len (struct pkt_file*) ; 
 int /*<<< orphan*/  skb_copy_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

uint _rtw_pktfile_read (struct pkt_file *pfile, u8 *rmem, uint rlen)
{
	uint	len = 0;

	len =  rtw_remainder_len(pfile);
	len = (rlen > len) ? len : rlen;

	if (rmem)
		skb_copy_bits(pfile->pkt, pfile->buf_len - pfile->pkt_len, rmem, len);

	pfile->cur_addr += len;
	pfile->pkt_len -= len;
	return len;
}