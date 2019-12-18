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
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BS_CMD_INIT_SYS_RUN ; 
 int /*<<< orphan*/  broadsheet_init_display (struct broadsheetfb_par*) ; 
 int /*<<< orphan*/  broadsheet_send_command (struct broadsheetfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void broadsheet_init(struct broadsheetfb_par *par)
{
	broadsheet_send_command(par, BS_CMD_INIT_SYS_RUN);
	/* the controller needs a second */
	msleep(1000);
	broadsheet_init_display(par);
}