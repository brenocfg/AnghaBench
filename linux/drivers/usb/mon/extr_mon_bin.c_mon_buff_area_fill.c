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
struct mon_reader_bin {int dummy; } ;
struct mon_bin_hdr {char type; scalar_t__ len_cap; } ;

/* Variables and functions */
 struct mon_bin_hdr* MON_OFF2HDR (struct mon_reader_bin const*,unsigned int) ; 
 scalar_t__ PKT_SIZE ; 
 int /*<<< orphan*/  memset (struct mon_bin_hdr*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mon_buff_area_fill(const struct mon_reader_bin *rp,
    unsigned int offset, unsigned int size)
{
	struct mon_bin_hdr *ep;

	ep = MON_OFF2HDR(rp, offset);
	memset(ep, 0, PKT_SIZE);
	ep->type = '@';
	ep->len_cap = size - PKT_SIZE;
}