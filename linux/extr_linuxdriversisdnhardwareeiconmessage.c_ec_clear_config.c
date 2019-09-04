#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dword ;
struct TYPE_5__ {int Id; int ec_idi_options; scalar_t__ ec_tail_length; TYPE_1__* adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 int LEC_ENABLE_ECHO_CANCELLER ; 
 int LEC_ENABLE_NONLINEAR_PROCESSING ; 
 int LEC_MANUAL_DISABLE ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ec_clear_config(PLCI *plci)
{

	dbug(1, dprintf("[%06lx] %s,%d: ec_clear_config",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__));

	plci->ec_idi_options = LEC_ENABLE_ECHO_CANCELLER |
		LEC_MANUAL_DISABLE | LEC_ENABLE_NONLINEAR_PROCESSING;
	plci->ec_tail_length = 0;
}