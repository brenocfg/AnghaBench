#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fraction; int /*<<< orphan*/  integer; } ;
struct TYPE_4__ {int /*<<< orphan*/  fraction; int /*<<< orphan*/  integer; } ;
struct scl_ratios_inits {TYPE_1__ v_init; TYPE_2__ h_init; int /*<<< orphan*/  v_int_scale_ratio; int /*<<< orphan*/  h_int_scale_ratio; } ;
struct dce_transform {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCL_AUTOMATIC_MODE_CONTROL ; 
 int /*<<< orphan*/  SCL_HORZ_FILTER_INIT ; 
 int /*<<< orphan*/  SCL_HORZ_FILTER_SCALE_RATIO ; 
 int /*<<< orphan*/  SCL_H_INIT_FRAC ; 
 int /*<<< orphan*/  SCL_H_INIT_INT ; 
 int /*<<< orphan*/  SCL_H_SCALE_RATIO ; 
 int /*<<< orphan*/  SCL_VERT_FILTER_INIT ; 
 int /*<<< orphan*/  SCL_VERT_FILTER_SCALE_RATIO ; 
 int /*<<< orphan*/  SCL_V_INIT_FRAC ; 
 int /*<<< orphan*/  SCL_V_INIT_INT ; 
 int /*<<< orphan*/  SCL_V_SCALE_RATIO ; 

__attribute__((used)) static void program_scl_ratios_inits(
	struct dce_transform *xfm_dce,
	struct scl_ratios_inits *inits)
{

	REG_SET(SCL_HORZ_FILTER_SCALE_RATIO, 0,
			SCL_H_SCALE_RATIO, inits->h_int_scale_ratio);

	REG_SET(SCL_VERT_FILTER_SCALE_RATIO, 0,
			SCL_V_SCALE_RATIO, inits->v_int_scale_ratio);

	REG_SET_2(SCL_HORZ_FILTER_INIT, 0,
			SCL_H_INIT_INT, inits->h_init.integer,
			SCL_H_INIT_FRAC, inits->h_init.fraction);

	REG_SET_2(SCL_VERT_FILTER_INIT, 0,
			SCL_V_INIT_INT, inits->v_init.integer,
			SCL_V_INIT_FRAC, inits->v_init.fraction);

	REG_WRITE(SCL_AUTOMATIC_MODE_CONTROL, 0);
}