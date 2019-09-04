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
typedef  int /*<<< orphan*/  nasid_t ;
typedef  int /*<<< orphan*/  cnodeid_t ;
struct TYPE_2__ {int /*<<< orphan*/  h_bigwin_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPACT_TO_NASID_NODEID (int /*<<< orphan*/ ) ; 
 unsigned int HUB_NUM_BIG_WINDOW ; 
 int /*<<< orphan*/  IIO_ITTE_DISABLE (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* hub_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hub_set_piomode (int /*<<< orphan*/ ) ; 

void hub_pio_init(cnodeid_t cnode)
{
	nasid_t nasid = COMPACT_TO_NASID_NODEID(cnode);
	unsigned i;

	/* initialize big window piomaps for this hub */
	bitmap_zero(hub_data(cnode)->h_bigwin_used, HUB_NUM_BIG_WINDOW);
	for (i = 0; i < HUB_NUM_BIG_WINDOW; i++)
		IIO_ITTE_DISABLE(nasid, i);

	hub_set_piomode(nasid);
}