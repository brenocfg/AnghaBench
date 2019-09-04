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

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 scalar_t__ MultReadInProgress ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fd_rwsec_done1 (int) ; 
 scalar_t__ read_track ; 
 int /*<<< orphan*/  readtrack_timer ; 

__attribute__((used)) static void fd_rwsec_done( int status )
{
	DPRINT(("fd_rwsec_done()\n"));

	if (read_track) {
		del_timer(&readtrack_timer);
		if (!MultReadInProgress)
			return;
		MultReadInProgress = 0;
	}
	fd_rwsec_done1(status);
}