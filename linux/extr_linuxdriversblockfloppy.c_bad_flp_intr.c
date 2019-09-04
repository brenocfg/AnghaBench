#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int abort; int reset; int recal; } ;
struct TYPE_12__ {TYPE_1__ max_errors; } ;
struct TYPE_11__ {int /*<<< orphan*/  track; int /*<<< orphan*/  probed_format; } ;
struct TYPE_10__ {int /*<<< orphan*/  badness; } ;
struct TYPE_9__ {int reset; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* done ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_6__* DP ; 
 TYPE_5__* DRS ; 
 TYPE_4__* DRWE ; 
 TYPE_3__* FDCS ; 
 int /*<<< orphan*/  INFBOUND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NEED_2_RECAL ; 
 TYPE_2__* cont ; 
 int* errors ; 
 int /*<<< orphan*/  next_valid_format () ; 
 scalar_t__ probing ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bad_flp_intr(void)
{
	int err_count;

	if (probing) {
		DRS->probed_format++;
		if (!next_valid_format())
			return;
	}
	err_count = ++(*errors);
	INFBOUND(DRWE->badness, err_count);
	if (err_count > DP->max_errors.abort)
		cont->done(0);
	if (err_count > DP->max_errors.reset)
		FDCS->reset = 1;
	else if (err_count > DP->max_errors.recal)
		DRS->track = NEED_2_RECAL;
}