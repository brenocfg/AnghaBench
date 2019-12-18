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
struct waveform_private {int /*<<< orphan*/  ao_timer; int /*<<< orphan*/  ai_timer; } ;
struct comedi_device {struct waveform_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void waveform_detach(struct comedi_device *dev)
{
	struct waveform_private *devpriv = dev->private;

	if (devpriv) {
		del_timer_sync(&devpriv->ai_timer);
		del_timer_sync(&devpriv->ao_timer);
	}
}