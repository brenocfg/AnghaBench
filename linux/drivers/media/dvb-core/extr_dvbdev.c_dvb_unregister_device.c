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
struct dvb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_free_device (struct dvb_device*) ; 
 int /*<<< orphan*/  dvb_remove_device (struct dvb_device*) ; 

void dvb_unregister_device(struct dvb_device *dvbdev)
{
	dvb_remove_device(dvbdev);
	dvb_free_device(dvbdev);
}