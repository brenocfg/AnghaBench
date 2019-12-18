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
struct subchannel_id {int ssid; int sch_no; } ;
struct idset {int num_id; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int,int) ; 

void idset_sch_del_subseq(struct idset *set, struct subchannel_id schid)
{
	int pos = schid.ssid * set->num_id + schid.sch_no;

	bitmap_clear(set->bitmap, pos, set->num_id - schid.sch_no);
}