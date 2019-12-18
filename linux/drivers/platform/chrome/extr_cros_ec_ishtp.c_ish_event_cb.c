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
struct ishtp_cl_rb {int dummy; } ;
struct ishtp_cl_device {int dummy; } ;
struct ishtp_cl {int dummy; } ;

/* Variables and functions */
 struct ishtp_cl_rb* ishtp_cl_rx_get_rb (struct ishtp_cl*) ; 
 struct ishtp_cl* ishtp_get_drvdata (struct ishtp_cl_device*) ; 
 int /*<<< orphan*/  process_recv (struct ishtp_cl*,struct ishtp_cl_rb*) ; 

__attribute__((used)) static void ish_event_cb(struct ishtp_cl_device *cl_device)
{
	struct ishtp_cl_rb *rb_in_proc;
	struct ishtp_cl	*cros_ish_cl = ishtp_get_drvdata(cl_device);

	while ((rb_in_proc = ishtp_cl_rx_get_rb(cros_ish_cl)) != NULL) {
		/* Decide what to do with received data */
		process_recv(cros_ish_cl, rb_in_proc);
	}
}