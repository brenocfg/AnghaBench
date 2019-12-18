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
typedef  int u32 ;
typedef  int u16 ;
struct hfi1_16b_header {int* lrh; } ;

/* Variables and functions */
 int OPA_16B_BECN_MASK ; 
 int OPA_16B_BECN_SHIFT ; 
 int OPA_16B_DLID_HIGH_SHIFT ; 
 int OPA_16B_DLID_MASK ; 
 int OPA_16B_DLID_SHIFT ; 
 int OPA_16B_FECN_MASK ; 
 int OPA_16B_FECN_SHIFT ; 
 int OPA_16B_L4_MASK ; 
 int OPA_16B_LEN_MASK ; 
 int OPA_16B_LEN_SHIFT ; 
 int OPA_16B_LID_MASK ; 
 int OPA_16B_PKEY_MASK ; 
 int OPA_16B_PKEY_SHIFT ; 
 int OPA_16B_SC_MASK ; 
 int OPA_16B_SC_SHIFT ; 
 int OPA_16B_SLID_HIGH_SHIFT ; 
 int OPA_16B_SLID_MASK ; 
 int OPA_16B_SLID_SHIFT ; 

__attribute__((used)) static inline void hfi1_make_16b_hdr(struct hfi1_16b_header *hdr,
				     u32 slid, u32 dlid,
				     u16 len, u16 pkey,
				     bool becn, bool fecn, u8 l4,
				     u8 sc)
{
	u32 lrh0 = 0;
	u32 lrh1 = 0x40000000;
	u32 lrh2 = 0;
	u32 lrh3 = 0;

	lrh0 = (lrh0 & ~OPA_16B_BECN_MASK) | (becn << OPA_16B_BECN_SHIFT);
	lrh0 = (lrh0 & ~OPA_16B_LEN_MASK) | (len << OPA_16B_LEN_SHIFT);
	lrh0 = (lrh0 & ~OPA_16B_LID_MASK)  | (slid & OPA_16B_LID_MASK);
	lrh1 = (lrh1 & ~OPA_16B_FECN_MASK) | (fecn << OPA_16B_FECN_SHIFT);
	lrh1 = (lrh1 & ~OPA_16B_SC_MASK) | (sc << OPA_16B_SC_SHIFT);
	lrh1 = (lrh1 & ~OPA_16B_LID_MASK) | (dlid & OPA_16B_LID_MASK);
	lrh2 = (lrh2 & ~OPA_16B_SLID_MASK) |
		((slid >> OPA_16B_SLID_SHIFT) << OPA_16B_SLID_HIGH_SHIFT);
	lrh2 = (lrh2 & ~OPA_16B_DLID_MASK) |
		((dlid >> OPA_16B_DLID_SHIFT) << OPA_16B_DLID_HIGH_SHIFT);
	lrh2 = (lrh2 & ~OPA_16B_PKEY_MASK) | ((u32)pkey << OPA_16B_PKEY_SHIFT);
	lrh2 = (lrh2 & ~OPA_16B_L4_MASK) | l4;

	hdr->lrh[0] = lrh0;
	hdr->lrh[1] = lrh1;
	hdr->lrh[2] = lrh2;
	hdr->lrh[3] = lrh3;
}