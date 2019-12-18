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
struct scif_endpt {scalar_t__ state; } ;

/* Variables and functions */
 int ECONNRESET ; 
 int ENODEV ; 
 int ENOTCONN ; 
 scalar_t__ SCIFEP_CONNECTED ; 
 scalar_t__ SCIFEP_DISCONNECTED ; 
 int /*<<< orphan*/  scifdev_alive (struct scif_endpt*) ; 

__attribute__((used)) static inline int scif_verify_epd(struct scif_endpt *ep)
{
	if (ep->state == SCIFEP_DISCONNECTED)
		return -ECONNRESET;

	if (ep->state != SCIFEP_CONNECTED)
		return -ENOTCONN;

	if (!scifdev_alive(ep))
		return -ENODEV;

	return 0;
}