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
struct ahd_softc {int /*<<< orphan*/  msg_type; scalar_t__ msgin_index; scalar_t__ msgout_len; int /*<<< orphan*/  msg_flags; scalar_t__ send_msg_perror; } ;
typedef  int /*<<< orphan*/  ahd_mode_state ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int ATNO ; 
 int CLRATNO ; 
 int /*<<< orphan*/  CLRSINT1 ; 
 int /*<<< orphan*/  MSG_FLAG_NONE ; 
 int MSG_NOOP ; 
 int /*<<< orphan*/  MSG_OUT ; 
 int /*<<< orphan*/  MSG_TYPE_NONE ; 
 int /*<<< orphan*/  SCSISIGO ; 
 int /*<<< orphan*/  SEQ_FLAGS2 ; 
 int TARGET_MSG_PENDING ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_restore_modes (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_save_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_clear_msg_state(struct ahd_softc *ahd)
{
	ahd_mode_state saved_modes;

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	ahd->send_msg_perror = 0;
	ahd->msg_flags = MSG_FLAG_NONE;
	ahd->msgout_len = 0;
	ahd->msgin_index = 0;
	ahd->msg_type = MSG_TYPE_NONE;
	if ((ahd_inb(ahd, SCSISIGO) & ATNO) != 0) {
		/*
		 * The target didn't care to respond to our
		 * message request, so clear ATN.
		 */
		ahd_outb(ahd, CLRSINT1, CLRATNO);
	}
	ahd_outb(ahd, MSG_OUT, MSG_NOOP);
	ahd_outb(ahd, SEQ_FLAGS2,
		 ahd_inb(ahd, SEQ_FLAGS2) & ~TARGET_MSG_PENDING);
	ahd_restore_modes(ahd, saved_modes);
}