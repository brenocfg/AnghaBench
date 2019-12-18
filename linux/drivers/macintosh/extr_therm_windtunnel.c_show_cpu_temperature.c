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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int temp; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 TYPE_1__ x ; 

__attribute__((used)) static ssize_t
show_cpu_temperature( struct device *dev, struct device_attribute *attr, char *buf )
{
	return sprintf(buf, "%d.%d\n", x.temp>>8, (x.temp & 255)*10/256 );
}