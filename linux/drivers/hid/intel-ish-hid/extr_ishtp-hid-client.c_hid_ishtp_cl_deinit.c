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
 int /*<<< orphan*/  ishtp_cl_flush_queues (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_free (struct ishtp_cl*) ; 
 int /*<<< orphan*/  ishtp_cl_unlink (struct ishtp_cl*) ; 

__attribute__((used)) static void hid_ishtp_cl_deinit(struct ishtp_cl *hid_ishtp_cl)
{
	ishtp_cl_unlink(hid_ishtp_cl);
	ishtp_cl_flush_queues(hid_ishtp_cl);

	/* disband and free all Tx and Rx client-level rings */
	ishtp_cl_free(hid_ishtp_cl);
}