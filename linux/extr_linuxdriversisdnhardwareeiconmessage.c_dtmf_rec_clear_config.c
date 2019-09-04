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
struct TYPE_5__ {int Id; TYPE_1__* adapter; int /*<<< orphan*/  capidtmf_state; scalar_t__ dtmf_rec_pause_ms; scalar_t__ dtmf_rec_pulse_ms; scalar_t__ dtmf_rec_active; } ;
struct TYPE_4__ {int /*<<< orphan*/  u_law; int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capidtmf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void dtmf_rec_clear_config(PLCI *plci)
{

	dbug(1, dprintf("[%06lx] %s,%d: dtmf_rec_clear_config",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__));

	plci->dtmf_rec_active = 0;
	plci->dtmf_rec_pulse_ms = 0;
	plci->dtmf_rec_pause_ms = 0;

	capidtmf_init(&(plci->capidtmf_state), plci->adapter->u_law);

}