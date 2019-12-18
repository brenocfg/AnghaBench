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
struct chsc_sei_nt2_area {int cc; int /*<<< orphan*/  ccdf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,int) ; 
 int /*<<< orphan*/  zpci_event_availability (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpci_event_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chsc_process_sei_nt2(struct chsc_sei_nt2_area *sei_area)
{
	switch (sei_area->cc) {
	case 1:
		zpci_event_error(sei_area->ccdf);
		break;
	case 2:
		zpci_event_availability(sei_area->ccdf);
		break;
	default:
		CIO_CRW_EVENT(2, "chsc: sei nt2 unhandled cc=%d\n",
			      sei_area->cc);
		break;
	}
}