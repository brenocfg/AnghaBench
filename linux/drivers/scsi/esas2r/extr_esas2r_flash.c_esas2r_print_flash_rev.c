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
typedef  int u8 ;
typedef  int u16 ;
struct esas2r_adapter {int /*<<< orphan*/  flash_rev; scalar_t__ flash_ver; } ;

/* Variables and functions */
 int HIBYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (scalar_t__) ; 
 int LOBYTE (int /*<<< orphan*/ ) ; 
 int LOWORD (scalar_t__) ; 
 int /*<<< orphan*/  esas2r_hdebug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

bool esas2r_print_flash_rev(struct esas2r_adapter *a)
{
	u16 year = LOWORD(a->flash_ver);
	u8 day = LOBYTE(HIWORD(a->flash_ver));
	u8 month = HIBYTE(HIWORD(a->flash_ver));

	if (day == 0
	    || month == 0
	    || day > 31
	    || month > 12
	    || year < 2006
	    || year > 9999) {
		strcpy(a->flash_rev, "not found");
		a->flash_ver = 0;
		return false;
	}

	sprintf(a->flash_rev, "%02d/%02d/%04d", month, day, year);
	esas2r_hdebug("flash version: %s", a->flash_rev);
	return true;
}