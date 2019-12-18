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
 int /*<<< orphan*/  ISIF_SYNCEN_WEN_MASK ; 
 int ISIF_SYNCEN_WEN_SHIFT ; 
 int /*<<< orphan*/  SYNCEN ; 
 int /*<<< orphan*/  reg_modify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isif_enable_output_to_sdram(int en)
{
	reg_modify(ISIF_SYNCEN_WEN_MASK, en << ISIF_SYNCEN_WEN_SHIFT, SYNCEN);
}