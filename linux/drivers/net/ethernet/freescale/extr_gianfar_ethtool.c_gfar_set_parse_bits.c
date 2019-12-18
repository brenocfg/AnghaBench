#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct filer_table {size_t index; TYPE_1__* fe; } ;
struct TYPE_2__ {int ctrl; int /*<<< orphan*/  prop; } ;

/* Variables and functions */
 int RQFCR_AND ; 
 int RQFCR_CMP_EXACT ; 
 int RQFCR_PID_PARSE ; 
 int /*<<< orphan*/  gfar_set_mask (int /*<<< orphan*/ ,struct filer_table*) ; 

__attribute__((used)) static void gfar_set_parse_bits(u32 value, u32 mask, struct filer_table *tab)
{
	gfar_set_mask(mask, tab);
	tab->fe[tab->index].ctrl = RQFCR_CMP_EXACT | RQFCR_PID_PARSE |
				   RQFCR_AND;
	tab->fe[tab->index].prop = value;
	tab->index++;
}