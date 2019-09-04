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
union drbd_state {scalar_t__ disk; int /*<<< orphan*/  conn; } ;
typedef  enum drbd_state_rv { ____Placeholder_drbd_state_rv } drbd_state_rv ;

/* Variables and functions */
 scalar_t__ D_DISKLESS ; 
 scalar_t__ D_FAILED ; 
 int SS_IS_DISKLESS ; 
 int is_valid_conn_transition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drbd_state_rv
is_valid_transition(union drbd_state os, union drbd_state ns)
{
	enum drbd_state_rv rv;

	rv = is_valid_conn_transition(os.conn, ns.conn);

	/* we cannot fail (again) if we already detached */
	if (ns.disk == D_FAILED && os.disk == D_DISKLESS)
		rv = SS_IS_DISKLESS;

	return rv;
}