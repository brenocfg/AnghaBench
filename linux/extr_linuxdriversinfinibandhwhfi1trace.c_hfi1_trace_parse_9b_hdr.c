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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ib_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_get_dlid (struct ib_header*) ; 
 int /*<<< orphan*/  ib_get_len (struct ib_header*) ; 
 int ib_get_lnh (struct ib_header*) ; 
 int ib_get_lver (struct ib_header*) ; 
 int ib_get_sc (struct ib_header*) ; 
 int ib_get_sl (struct ib_header*) ; 
 int /*<<< orphan*/  ib_get_slid (struct ib_header*) ; 

void hfi1_trace_parse_9b_hdr(struct ib_header *hdr, bool sc5,
			     u8 *lnh, u8 *lver, u8 *sl, u8 *sc,
			     u16 *len, u32 *dlid, u32 *slid)
{
	*lnh = ib_get_lnh(hdr);
	*lver = ib_get_lver(hdr);
	*sl = ib_get_sl(hdr);
	*sc = ib_get_sc(hdr) | (sc5 << 4);
	*len = ib_get_len(hdr);
	*dlid = ib_get_dlid(hdr);
	*slid = ib_get_slid(hdr);
}