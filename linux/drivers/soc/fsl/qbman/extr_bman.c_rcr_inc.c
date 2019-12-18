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
struct bm_rcr_entry {int dummy; } ;
struct bm_rcr {int /*<<< orphan*/  vbit; struct bm_rcr_entry* cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_RCR_VERB_VBIT ; 
 struct bm_rcr_entry* rcr_carryclear (struct bm_rcr_entry*) ; 

__attribute__((used)) static inline void rcr_inc(struct bm_rcr *rcr)
{
	/* increment to the next RCR pointer and handle overflow and 'vbit' */
	struct bm_rcr_entry *partial = rcr->cursor + 1;

	rcr->cursor = rcr_carryclear(partial);
	if (partial != rcr->cursor)
		rcr->vbit ^= BM_RCR_VERB_VBIT;
}