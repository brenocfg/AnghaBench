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
struct intel_guc {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/  const) ; 

int intel_guc_send_nop(struct intel_guc *guc, const u32 *action, u32 len,
		       u32 *response_buf, u32 response_buf_size)
{
	WARN(1, "Unexpected send: action=%#x\n", *action);
	return -ENODEV;
}