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
typedef  int /*<<< orphan*/  u16 ;
struct broadsheetfb_par {TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_ctl ) (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* wait_for_rdy ) (struct broadsheetfb_par*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BS_CS ; 
 int /*<<< orphan*/  BS_DC ; 
 int /*<<< orphan*/  broadsheet_gpio_issue_cmd (struct broadsheetfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  broadsheet_gpio_issue_data (struct broadsheetfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct broadsheetfb_par*) ; 
 int /*<<< orphan*/  stub2 (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct broadsheetfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void broadsheet_gpio_send_cmdargs(struct broadsheetfb_par *par, u16 cmd,
					int argc, u16 *argv)
{
	int i;

	par->board->wait_for_rdy(par);

	par->board->set_ctl(par, BS_CS, 0);
	broadsheet_gpio_issue_cmd(par, cmd);
	par->board->set_ctl(par, BS_DC, 1);

	for (i = 0; i < argc; i++)
		broadsheet_gpio_issue_data(par, argv[i]);
	par->board->set_ctl(par, BS_CS, 1);
}