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
struct TYPE_2__ {scalar_t__ act_dist; } ;
struct cyttsp {TYPE_1__ xy_data; } ;

/* Variables and functions */
 scalar_t__ CY_ACT_DIST_DFLT ; 
 int /*<<< orphan*/  CY_OPERATE_MODE ; 
 int /*<<< orphan*/  CY_REG_BASE ; 
 int EIO ; 
 int cyttsp_handshake (struct cyttsp*) ; 
 int ttsp_read_block_data (struct cyttsp*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int ttsp_send_command (struct cyttsp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyttsp_set_operational_mode(struct cyttsp *ts)
{
	int error;

	error = ttsp_send_command(ts, CY_OPERATE_MODE);
	if (error)
		return error;

	/* wait for TTSP Device to complete switch to Operational mode */
	error = ttsp_read_block_data(ts, CY_REG_BASE,
				     sizeof(ts->xy_data), &ts->xy_data);
	if (error)
		return error;

	error = cyttsp_handshake(ts);
	if (error)
		return error;

	return ts->xy_data.act_dist == CY_ACT_DIST_DFLT ? -EIO : 0;
}