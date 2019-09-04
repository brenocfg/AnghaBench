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
 int /*<<< orphan*/  __raid10_far_copies (int) ; 
 int /*<<< orphan*/  __raid10_near_copies (int) ; 
 unsigned int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int raid10_md_layout_to_copies(int layout)
{
	return max(__raid10_near_copies(layout), __raid10_far_copies(layout));
}