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
struct TYPE_2__ {scalar_t__ msg_len; } ;
struct av7110 {int /*<<< orphan*/  fe; int /*<<< orphan*/  saved_tone; int /*<<< orphan*/  saved_minicmd; TYPE_1__ saved_master_cmd; int /*<<< orphan*/  saved_voltage; } ;

/* Variables and functions */
 int /*<<< orphan*/  av7110_fe_diseqc_send_burst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av7110_fe_diseqc_send_master_cmd (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  av7110_fe_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av7110_fe_set_frontend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av7110_fe_set_tone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av7110_fe_set_voltage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void dvb_s_recover(struct av7110* av7110)
{
	av7110_fe_init(av7110->fe);

	av7110_fe_set_voltage(av7110->fe, av7110->saved_voltage);
	if (av7110->saved_master_cmd.msg_len) {
		msleep(20);
		av7110_fe_diseqc_send_master_cmd(av7110->fe, &av7110->saved_master_cmd);
	}
	msleep(20);
	av7110_fe_diseqc_send_burst(av7110->fe, av7110->saved_minicmd);
	msleep(20);
	av7110_fe_set_tone(av7110->fe, av7110->saved_tone);

	av7110_fe_set_frontend(av7110->fe);
}