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
struct sta_info {int dummy; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Update_RA_Entry (struct adapter*,struct sta_info*) ; 

void set_sta_rate(struct adapter *padapter, struct sta_info *psta)
{
	/* rate adaptive */
	Update_RA_Entry(padapter, psta);
}