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
typedef  int u16 ;
struct hfi1_pportdata {int part_enforce; int /*<<< orphan*/ * pkeys; } ;

/* Variables and functions */
 int HFI1_PART_ENFORCE_IN ; 
 int PKEY_LOW_15_MASK ; 
 scalar_t__ ingress_pkey_matches_entry (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ingress_pkey_table_fail (struct hfi1_pportdata*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ingress_pkey_table_search (struct hfi1_pportdata*,int) ; 

__attribute__((used)) static inline int ingress_pkey_check(struct hfi1_pportdata *ppd, u16 pkey,
				     u8 sc5, u8 idx, u32 slid, bool force)
{
	if (!(force) && !(ppd->part_enforce & HFI1_PART_ENFORCE_IN))
		return 0;

	/* If SC15, pkey[0:14] must be 0x7fff */
	if ((sc5 == 0xf) && ((pkey & PKEY_LOW_15_MASK) != PKEY_LOW_15_MASK))
		goto bad;

	/* Is the pkey = 0x0, or 0x8000? */
	if ((pkey & PKEY_LOW_15_MASK) == 0)
		goto bad;

	/* The most likely matching pkey has index 'idx' */
	if (ingress_pkey_matches_entry(pkey, ppd->pkeys[idx]))
		return 0;

	/* no match - try the whole table */
	if (!ingress_pkey_table_search(ppd, pkey))
		return 0;

bad:
	ingress_pkey_table_fail(ppd, pkey, slid);
	return 1;
}