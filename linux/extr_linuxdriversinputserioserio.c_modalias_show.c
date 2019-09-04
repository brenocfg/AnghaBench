#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; int proto; int id; int extra; } ;
struct serio {TYPE_1__ id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int,int) ; 
 struct serio* to_serio_port (struct device*) ; 

__attribute__((used)) static ssize_t modalias_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct serio *serio = to_serio_port(dev);

	return sprintf(buf, "serio:ty%02Xpr%02Xid%02Xex%02X\n",
			serio->id.type, serio->id.proto, serio->id.id, serio->id.extra);
}