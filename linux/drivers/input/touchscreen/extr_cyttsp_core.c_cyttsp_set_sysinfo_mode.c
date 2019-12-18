#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tts_verl; int /*<<< orphan*/  tts_verh; } ;
struct cyttsp {TYPE_1__ sysinfo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CY_DELAY_DFLT ; 
 int /*<<< orphan*/  CY_REG_BASE ; 
 int /*<<< orphan*/  CY_SYSINFO_MODE ; 
 int EIO ; 
 int cyttsp_handshake (struct cyttsp*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int ttsp_read_block_data (struct cyttsp*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int ttsp_send_command (struct cyttsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyttsp_set_sysinfo_mode(struct cyttsp *ts)
{
	int error;

	memset(&ts->sysinfo_data, 0, sizeof(ts->sysinfo_data));

	/* switch to sysinfo mode */
	error = ttsp_send_command(ts, CY_SYSINFO_MODE);
	if (error)
		return error;

	/* read sysinfo registers */
	msleep(CY_DELAY_DFLT);
	error = ttsp_read_block_data(ts, CY_REG_BASE, sizeof(ts->sysinfo_data),
				      &ts->sysinfo_data);
	if (error)
		return error;

	error = cyttsp_handshake(ts);
	if (error)
		return error;

	if (!ts->sysinfo_data.tts_verh && !ts->sysinfo_data.tts_verl)
		return -EIO;

	return 0;
}