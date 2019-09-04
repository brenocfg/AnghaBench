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
struct sony_sc {int quirks; } ;

/* Variables and functions */
 int SONY_BT_DEVICE ; 

__attribute__((used)) static inline int sony_compare_connection_type(struct sony_sc *sc0,
						struct sony_sc *sc1)
{
	const int sc0_not_bt = !(sc0->quirks & SONY_BT_DEVICE);
	const int sc1_not_bt = !(sc1->quirks & SONY_BT_DEVICE);

	return sc0_not_bt == sc1_not_bt;
}