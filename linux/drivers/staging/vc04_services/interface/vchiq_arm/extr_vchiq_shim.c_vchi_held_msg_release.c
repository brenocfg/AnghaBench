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
struct vchiq_header {int dummy; } ;
struct vchi_held_msg {scalar_t__ message; scalar_t__ service; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_release_message (int /*<<< orphan*/ ,struct vchiq_header*) ; 

int32_t vchi_held_msg_release(struct vchi_held_msg *message)
{
	/*
	 * Convert the service field pointer back to an
	 * VCHIQ_SERVICE_HANDLE_T which is an int.
	 * This pointer is opaque to everything except
	 * vchi_msg_hold which simply upcasted the int
	 * to a pointer.
	 */

	vchiq_release_message((VCHIQ_SERVICE_HANDLE_T)(long)message->service,
			      (struct vchiq_header *)message->message);

	return 0;
}