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
struct TYPE_2__ {scalar_t__ loopback; int /*<<< orphan*/  clock_speed; } ;
struct mgsl_struct {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  usc_enable_aux_clock (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_enable_loopback (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_loopback_frame (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_set_sdlc_mode (struct mgsl_struct*) ; 

__attribute__((used)) static void usc_set_sync_mode( struct mgsl_struct *info )
{
	usc_loopback_frame( info );
	usc_set_sdlc_mode( info );

	usc_enable_aux_clock(info, info->params.clock_speed);

	if (info->params.loopback)
		usc_enable_loopback(info,1);

}