#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ascebc; } ;
struct con3270 {scalar_t__ nr_up; int /*<<< orphan*/  update_flags; TYPE_2__* status; TYPE_1__ view; } ;
struct TYPE_4__ {scalar_t__ string; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_UPDATE_STATUS ; 
 int /*<<< orphan*/  codepage_convert (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 

__attribute__((used)) static void
con3270_update_status(struct con3270 *cp)
{
	char *str;

	str = (cp->nr_up != 0) ? "History" : "Running";
	memcpy(cp->status->string + 24, str, 7);
	codepage_convert(cp->view.ascebc, cp->status->string + 24, 7);
	cp->update_flags |= CON_UPDATE_STATUS;
}