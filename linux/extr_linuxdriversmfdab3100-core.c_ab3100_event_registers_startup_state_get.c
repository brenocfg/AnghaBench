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
typedef  int /*<<< orphan*/  u8 ;
struct device {int /*<<< orphan*/  parent; } ;
struct ab3100 {int /*<<< orphan*/  startup_events; int /*<<< orphan*/  startup_events_read; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct ab3100* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ab3100_event_registers_startup_state_get(struct device *dev,
					     u8 *event)
{
	struct ab3100 *ab3100 = dev_get_drvdata(dev->parent);

	if (!ab3100->startup_events_read)
		return -EAGAIN; /* Try again later */
	memcpy(event, ab3100->startup_events, 3);

	return 0;
}