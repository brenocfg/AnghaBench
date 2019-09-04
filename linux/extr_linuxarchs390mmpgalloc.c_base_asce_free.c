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

/* Variables and functions */
 unsigned long _ASCE_ORIGIN ; 
 unsigned long _ASCE_TYPE_MASK ; 
#define  _ASCE_TYPE_REGION1 131 
#define  _ASCE_TYPE_REGION2 130 
#define  _ASCE_TYPE_REGION3 129 
#define  _ASCE_TYPE_SEGMENT 128 
 int /*<<< orphan*/  _PAGE_SIZE ; 
 int /*<<< orphan*/  _REGION1_SIZE ; 
 int /*<<< orphan*/  _REGION2_SIZE ; 
 int /*<<< orphan*/  _REGION3_SIZE ; 
 int /*<<< orphan*/  base_crst_free (unsigned long) ; 
 int /*<<< orphan*/  base_region1_walk (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_region2_walk (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_region3_walk (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_segment_walk (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void base_asce_free(unsigned long asce)
{
	unsigned long table = asce & _ASCE_ORIGIN;

	if (!asce)
		return;
	switch (asce & _ASCE_TYPE_MASK) {
	case _ASCE_TYPE_SEGMENT:
		base_segment_walk(table, 0, _REGION3_SIZE, 0);
		break;
	case _ASCE_TYPE_REGION3:
		base_region3_walk(table, 0, _REGION2_SIZE, 0);
		break;
	case _ASCE_TYPE_REGION2:
		base_region2_walk(table, 0, _REGION1_SIZE, 0);
		break;
	case _ASCE_TYPE_REGION1:
		base_region1_walk(table, 0, -_PAGE_SIZE, 0);
		break;
	}
	base_crst_free(table);
}