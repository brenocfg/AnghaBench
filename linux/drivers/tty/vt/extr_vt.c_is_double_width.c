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
typedef  scalar_t__ uint32_t ;
struct interval {int member_0; int member_1; scalar_t__ first; scalar_t__ last; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct interval const*) ; 
 int /*<<< orphan*/ * bsearch (scalar_t__*,struct interval const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucs_cmp ; 

__attribute__((used)) static int is_double_width(uint32_t ucs)
{
	static const struct interval double_width[] = {
		{ 0x1100, 0x115F }, { 0x2329, 0x232A }, { 0x2E80, 0x303E },
		{ 0x3040, 0xA4CF }, { 0xAC00, 0xD7A3 }, { 0xF900, 0xFAFF },
		{ 0xFE10, 0xFE19 }, { 0xFE30, 0xFE6F }, { 0xFF00, 0xFF60 },
		{ 0xFFE0, 0xFFE6 }, { 0x20000, 0x2FFFD }, { 0x30000, 0x3FFFD }
	};
	if (ucs < double_width[0].first ||
	    ucs > double_width[ARRAY_SIZE(double_width) - 1].last)
		return 0;

	return bsearch(&ucs, double_width, ARRAY_SIZE(double_width),
			sizeof(struct interval), ucs_cmp) != NULL;
}