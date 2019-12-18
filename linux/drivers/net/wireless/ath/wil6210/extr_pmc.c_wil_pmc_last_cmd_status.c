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
struct TYPE_2__ {int last_cmd_status; } ;
struct wil6210_priv {TYPE_1__ pmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  wil_dbg_misc (struct wil6210_priv*,char*,int) ; 

int wil_pmc_last_cmd_status(struct wil6210_priv *wil)
{
	wil_dbg_misc(wil, "pmc_last_cmd_status: status %d\n",
		     wil->pmc.last_cmd_status);

	return wil->pmc.last_cmd_status;
}