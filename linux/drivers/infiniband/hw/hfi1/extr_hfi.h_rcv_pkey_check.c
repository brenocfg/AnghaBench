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
typedef  int u16 ;
struct hfi1_pportdata {int part_enforce; } ;

/* Variables and functions */
 int HFI1_PART_ENFORCE_IN ; 
 int PKEY_LOW_15_MASK ; 
 int /*<<< orphan*/  ingress_pkey_table_fail (struct hfi1_pportdata*,int,int) ; 

__attribute__((used)) static inline int rcv_pkey_check(struct hfi1_pportdata *ppd, u16 pkey,
				 u8 sc5, u16 slid)
{
	if (!(ppd->part_enforce & HFI1_PART_ENFORCE_IN))
		return 0;

	/* If SC15, pkey[0:14] must be 0x7fff */
	if ((sc5 == 0xf) && ((pkey & PKEY_LOW_15_MASK) != PKEY_LOW_15_MASK))
		goto bad;

	return 0;
bad:
	ingress_pkey_table_fail(ppd, pkey, slid);
	return 1;
}