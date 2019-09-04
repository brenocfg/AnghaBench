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
struct TYPE_2__ {int /*<<< orphan*/  sms_sysconfig; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMS_SYSCONFIG ; 
 TYPE_1__ sms_context ; 
 int /*<<< orphan*/  sms_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap2_sms_restore_context(void)
{
	sms_write_reg(sms_context.sms_sysconfig, SMS_SYSCONFIG);
}