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
typedef  int /*<<< orphan*/  u16 ;
struct ib_header {void** lrh; } ;

/* Variables and functions */
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hfi1_make_ib_hdr(struct ib_header *hdr,
				    u16 lrh0, u16 len,
				    u16 dlid, u16 slid)
{
	hdr->lrh[0] = cpu_to_be16(lrh0);
	hdr->lrh[1] = cpu_to_be16(dlid);
	hdr->lrh[2] = cpu_to_be16(len);
	hdr->lrh[3] = cpu_to_be16(slid);
}