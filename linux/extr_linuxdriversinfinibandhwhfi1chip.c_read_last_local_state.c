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
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENERAL_CONFIG ; 
 int /*<<< orphan*/  LAST_LOCAL_STATE_COMPLETE ; 
 int /*<<< orphan*/  read_8051_config (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_last_local_state(struct hfi1_devdata *dd, u32 *lls)
{
	read_8051_config(dd, LAST_LOCAL_STATE_COMPLETE, GENERAL_CONFIG, lls);
}