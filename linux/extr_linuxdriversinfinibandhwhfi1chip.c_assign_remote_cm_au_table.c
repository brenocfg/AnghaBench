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
typedef  int /*<<< orphan*/  u8 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_CM_REMOTE_AU_TABLE0_TO3 ; 
 int /*<<< orphan*/  SEND_CM_REMOTE_AU_TABLE4_TO7 ; 
 int /*<<< orphan*/  assign_cm_au_table (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcu_to_cu (int /*<<< orphan*/ ) ; 

void assign_remote_cm_au_table(struct hfi1_devdata *dd, u8 vcu)
{
	assign_cm_au_table(dd, vcu_to_cu(vcu), SEND_CM_REMOTE_AU_TABLE0_TO3,
			   SEND_CM_REMOTE_AU_TABLE4_TO7);
}