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
struct inno_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_SYS_CTRL ; 
 int /*<<< orphan*/  hdmi_modb (struct inno_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_POWER ; 
 int /*<<< orphan*/  v_PWR_OFF ; 
 int /*<<< orphan*/  v_PWR_ON ; 

__attribute__((used)) static void inno_hdmi_sys_power(struct inno_hdmi *hdmi, bool enable)
{
	if (enable)
		hdmi_modb(hdmi, HDMI_SYS_CTRL, m_POWER, v_PWR_ON);
	else
		hdmi_modb(hdmi, HDMI_SYS_CTRL, m_POWER, v_PWR_OFF);
}