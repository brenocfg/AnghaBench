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
struct serio {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  serio_cleanup (struct serio*) ; 
 struct serio* to_serio_port (struct device*) ; 

__attribute__((used)) static void serio_shutdown(struct device *dev)
{
	struct serio *serio = to_serio_port(dev);

	serio_cleanup(serio);
}