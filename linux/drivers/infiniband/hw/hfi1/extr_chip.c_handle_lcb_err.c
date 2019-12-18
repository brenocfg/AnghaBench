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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_devdata {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcb_err_string (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_lcb_err(struct hfi1_devdata *dd, u32 unused, u64 reg)
{
	char buf[96];

	dd_dev_info(dd, "LCB Error: %s\n",
		    lcb_err_string(buf, sizeof(buf), reg));
}