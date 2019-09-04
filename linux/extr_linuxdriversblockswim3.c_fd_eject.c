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
struct floppy_state {int ejected; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_IN ; 
 int EINTR ; 
 int /*<<< orphan*/  EJECT ; 
 int /*<<< orphan*/  RELAX ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  ejecting ; 
 int grab_drive (struct floppy_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_drive (struct floppy_state*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swim3_action (struct floppy_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ swim3_readbit (struct floppy_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swim3_select (struct floppy_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int fd_eject(struct floppy_state *fs)
{
	int err, n;

	err = grab_drive(fs, ejecting, 1);
	if (err)
		return err;
	swim3_action(fs, EJECT);
	for (n = 20; n > 0; --n) {
		if (signal_pending(current)) {
			err = -EINTR;
			break;
		}
		swim3_select(fs, RELAX);
		schedule_timeout_interruptible(1);
		if (swim3_readbit(fs, DISK_IN) == 0)
			break;
	}
	swim3_select(fs, RELAX);
	udelay(150);
	fs->ejected = 1;
	release_drive(fs);
	return err;
}