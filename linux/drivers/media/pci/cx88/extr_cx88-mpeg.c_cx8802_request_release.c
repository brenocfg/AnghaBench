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
struct cx88_core {scalar_t__ active_ref; int /*<<< orphan*/  active_type_id; int /*<<< orphan*/  last_analog_input; int /*<<< orphan*/  input; } ;
struct cx8802_driver {scalar_t__ type_id; int /*<<< orphan*/  (* advise_release ) (struct cx8802_driver*) ;struct cx88_core* core; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX88_BOARD_NONE ; 
 scalar_t__ CX88_MPEG_DVB ; 
 int /*<<< orphan*/  MO_GP0_IO ; 
 int /*<<< orphan*/  cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cx8802_driver*) ; 

__attribute__((used)) static int cx8802_request_release(struct cx8802_driver *drv)
{
	struct cx88_core *core = drv->core;

	if (drv->advise_release && --core->active_ref == 0) {
		if (drv->type_id == CX88_MPEG_DVB) {
			/*
			 * If the DVB driver is releasing, reset the input
			 * state to the last configured analog input
			 */
			core->input = core->last_analog_input;
		}

		drv->advise_release(drv);
		core->active_type_id = CX88_BOARD_NONE;
		dprintk(1, "Post release GPIO=%x\n", cx_read(MO_GP0_IO));
	}

	return 0;
}