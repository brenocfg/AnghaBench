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
typedef  struct atkbd atkbd ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct atkbd* serio_get_drvdata (struct serio*) ; 
 struct serio* to_serio_port (struct device*) ; 

__attribute__((used)) static ssize_t atkbd_attr_show_helper(struct device *dev, char *buf,
				ssize_t (*handler)(struct atkbd *, char *))
{
	struct serio *serio = to_serio_port(dev);
	struct atkbd *atkbd = serio_get_drvdata(serio);

	return handler(atkbd, buf);
}