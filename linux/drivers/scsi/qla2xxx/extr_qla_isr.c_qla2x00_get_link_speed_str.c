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
typedef  int uint16_t ;
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_QLA2100 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2200 (struct qla_hw_data*) ; 
 size_t LS_UNKNOWN ; 
 size_t QLA_LAST_SPEED ; 

const char *
qla2x00_get_link_speed_str(struct qla_hw_data *ha, uint16_t speed)
{
	static const char *const link_speeds[] = {
		"1", "2", "?", "4", "8", "16", "32", "10"
	};
#define	QLA_LAST_SPEED (ARRAY_SIZE(link_speeds) - 1)

	if (IS_QLA2100(ha) || IS_QLA2200(ha))
		return link_speeds[0];
	else if (speed == 0x13)
		return link_speeds[QLA_LAST_SPEED];
	else if (speed < QLA_LAST_SPEED)
		return link_speeds[speed];
	else
		return link_speeds[LS_UNKNOWN];
}