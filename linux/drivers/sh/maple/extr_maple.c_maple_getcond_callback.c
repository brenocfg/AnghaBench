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
struct maple_device {void (* callback ) (struct mapleq*) ;unsigned long interval; int /*<<< orphan*/  when; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (unsigned long) ; 
 int /*<<< orphan*/  jiffies ; 

void maple_getcond_callback(struct maple_device *dev,
			void (*callback) (struct mapleq *mq),
			unsigned long interval, unsigned long function)
{
	dev->callback = callback;
	dev->interval = interval;
	dev->function = cpu_to_be32(function);
	dev->when = jiffies;
}