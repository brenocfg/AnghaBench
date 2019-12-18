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
struct cx88_input {int dummy; } ;
struct TYPE_4__ {TYPE_1__* input; } ;
struct cx88_core {scalar_t__ active_type_id; unsigned int last_analog_input; unsigned int input; int /*<<< orphan*/  active_ref; TYPE_2__ board; } ;
struct cx8802_driver {scalar_t__ type_id; int /*<<< orphan*/  (* advise_acquire ) (struct cx8802_driver*) ;struct cx88_core* core; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CX88_BOARD_NONE ; 
 scalar_t__ CX88_MPEG_DVB ; 
 scalar_t__ CX88_VMUX_DVB ; 
 int EBUSY ; 
 int /*<<< orphan*/  MO_GP0_IO ; 
 int /*<<< orphan*/  cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cx8802_driver*) ; 

__attribute__((used)) static int cx8802_request_acquire(struct cx8802_driver *drv)
{
	struct cx88_core *core = drv->core;
	unsigned int	i;

	/* Fail a request for hardware if the device is busy. */
	if (core->active_type_id != CX88_BOARD_NONE &&
	    core->active_type_id != drv->type_id)
		return -EBUSY;

	if (drv->type_id == CX88_MPEG_DVB) {
		/* When switching to DVB, always set the input to the tuner */
		core->last_analog_input = core->input;
		core->input = 0;
		for (i = 0;
		     i < (sizeof(core->board.input) /
			  sizeof(struct cx88_input));
		     i++) {
			if (core->board.input[i].type == CX88_VMUX_DVB) {
				core->input = i;
				break;
			}
		}
	}

	if (drv->advise_acquire) {
		core->active_ref++;
		if (core->active_type_id == CX88_BOARD_NONE) {
			core->active_type_id = drv->type_id;
			drv->advise_acquire(drv);
		}

		dprintk(1, "Post acquire GPIO=%x\n", cx_read(MO_GP0_IO));
	}

	return 0;
}