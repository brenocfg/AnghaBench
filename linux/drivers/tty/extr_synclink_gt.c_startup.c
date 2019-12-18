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
struct TYPE_5__ {TYPE_1__* tty; } ;
struct slgt_info {TYPE_2__ port; int /*<<< orphan*/  icount; scalar_t__ pending_bh; int /*<<< orphan*/  device_name; scalar_t__ tx_buf; int /*<<< orphan*/  max_frame_size; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGERR (char*) ; 
 int /*<<< orphan*/  DBGINFO (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  change_params (struct slgt_info*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tty_port_initialized (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_port_set_initialized (TYPE_2__*,int) ; 

__attribute__((used)) static int startup(struct slgt_info *info)
{
	DBGINFO(("%s startup\n", info->device_name));

	if (tty_port_initialized(&info->port))
		return 0;

	if (!info->tx_buf) {
		info->tx_buf = kmalloc(info->max_frame_size, GFP_KERNEL);
		if (!info->tx_buf) {
			DBGERR(("%s can't allocate tx buffer\n", info->device_name));
			return -ENOMEM;
		}
	}

	info->pending_bh = 0;

	memset(&info->icount, 0, sizeof(info->icount));

	/* program hardware for current parameters */
	change_params(info);

	if (info->port.tty)
		clear_bit(TTY_IO_ERROR, &info->port.tty->flags);

	tty_port_set_initialized(&info->port, 1);

	return 0;
}