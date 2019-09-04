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
typedef  int u32 ;
struct lanai_dev {int status; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int STATUS_GPIN ; 
 int STATUS_LED ; 
 int STATUS_LOCD ; 
 int STATUS_SOOL ; 
 int /*<<< orphan*/  Status_Reg ; 
 int reg_read (struct lanai_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_message (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void lanai_check_status(struct lanai_dev *lanai)
{
	u32 new = reg_read(lanai, Status_Reg);
	u32 changes = new ^ lanai->status;
	lanai->status = new;
#define e(flag, name) \
		if (changes & flag) \
			status_message(lanai->number, name, new & flag)
	e(STATUS_SOOL, "SOOL");
	e(STATUS_LOCD, "LOCD");
	e(STATUS_LED, "LED");
	e(STATUS_GPIN, "GPIN");
#undef e
}