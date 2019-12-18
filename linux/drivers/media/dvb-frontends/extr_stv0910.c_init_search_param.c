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
struct stv {int dummy; } ;
struct dtv_frontend_properties {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILTER_EN ; 
 int /*<<< orphan*/  FORCE_CONTINUOUS ; 
 int /*<<< orphan*/  FRAME_MODE ; 
 int /*<<< orphan*/  HYSTERESIS_THRESHOLD ; 
 int /*<<< orphan*/  ISIOBS_MODE ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TSDEL_SYNCBYTE ; 
 int /*<<< orphan*/  TSFIFO_EMBINDVB ; 
 int /*<<< orphan*/  TSINS_TOKEN ; 
 int /*<<< orphan*/  TSOUT_NOSYNC ; 
 int /*<<< orphan*/  UPLCCST0 ; 
 int /*<<< orphan*/  set_stream_modes (struct stv*,struct dtv_frontend_properties*) ; 

__attribute__((used)) static int init_search_param(struct stv *state,
			     struct dtv_frontend_properties *p)
{
	SET_FIELD(FORCE_CONTINUOUS, 0);
	SET_FIELD(FRAME_MODE, 0);
	SET_FIELD(FILTER_EN, 0);
	SET_FIELD(TSOUT_NOSYNC, 0);
	SET_FIELD(TSFIFO_EMBINDVB, 0);
	SET_FIELD(TSDEL_SYNCBYTE, 0);
	SET_REG(UPLCCST0, 0xe0);
	SET_FIELD(TSINS_TOKEN, 0);
	SET_FIELD(HYSTERESIS_THRESHOLD, 0);
	SET_FIELD(ISIOBS_MODE, 1);

	set_stream_modes(state, p);
	return 0;
}