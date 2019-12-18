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
struct ishtp_cl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISHTP_CL_DISCONNECTING ; 
 int /*<<< orphan*/  ishtp_cl_disconnect (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_flush_queues (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_free (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_unlink (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_set_connection_state (struct ishtp_cl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cros_ish_deinit(struct ishtp_cl *cros_ish_cl)
{
	ishtp_set_connection_state(cros_ish_cl, ISHTP_CL_DISCONNECTING);
	ishtp_cl_disconnect(cros_ish_cl);
	ishtp_cl_unlink(cros_ish_cl);
	ishtp_cl_flush_queues(cros_ish_cl);

	/* Disband and free all Tx and Rx client-level rings */
	ishtp_cl_free(cros_ish_cl);
}