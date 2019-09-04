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
struct TYPE_2__ {int hst_mode; } ;
struct cyttsp {TYPE_1__ xy_data; scalar_t__ use_hndshk; } ;

/* Variables and functions */
 int CY_HNDSHK_BIT ; 
 int ttsp_send_command (struct cyttsp*,int) ; 

__attribute__((used)) static int cyttsp_handshake(struct cyttsp *ts)
{
	if (ts->use_hndshk)
		return ttsp_send_command(ts,
				ts->xy_data.hst_mode ^ CY_HNDSHK_BIT);

	return 0;
}