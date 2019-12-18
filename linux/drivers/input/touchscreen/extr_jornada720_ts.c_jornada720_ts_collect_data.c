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
struct jornada_ts {void** y_data; void** x_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXDUMMY ; 
 void* jornada_ssp_byte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jornada720_ts_collect_data(struct jornada_ts *jornada_ts)
{
	/* 3 low word X samples */
	jornada_ts->x_data[0] = jornada_ssp_byte(TXDUMMY);
	jornada_ts->x_data[1] = jornada_ssp_byte(TXDUMMY);
	jornada_ts->x_data[2] = jornada_ssp_byte(TXDUMMY);

	/* 3 low word Y samples */
	jornada_ts->y_data[0] = jornada_ssp_byte(TXDUMMY);
	jornada_ts->y_data[1] = jornada_ssp_byte(TXDUMMY);
	jornada_ts->y_data[2] = jornada_ssp_byte(TXDUMMY);

	/* combined x samples bits */
	jornada_ts->x_data[3] = jornada_ssp_byte(TXDUMMY);

	/* combined y samples bits */
	jornada_ts->y_data[3] = jornada_ssp_byte(TXDUMMY);
}