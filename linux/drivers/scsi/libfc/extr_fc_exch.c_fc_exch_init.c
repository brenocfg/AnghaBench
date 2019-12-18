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
struct TYPE_2__ {scalar_t__ exch_mgr_reset; } ;
struct fc_lport {TYPE_1__ tt; } ;

/* Variables and functions */
 scalar_t__ fc_exch_mgr_reset ; 

int fc_exch_init(struct fc_lport *lport)
{
	if (!lport->tt.exch_mgr_reset)
		lport->tt.exch_mgr_reset = fc_exch_mgr_reset;

	return 0;
}