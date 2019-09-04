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
typedef  int /*<<< orphan*/  lboard_t ;
typedef  int /*<<< orphan*/  klinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/ * find_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char) ; 

klinfo_t *find_first_component(lboard_t *brd, unsigned char struct_type)
{
	return find_component(brd, (klinfo_t *)NULL, struct_type);
}