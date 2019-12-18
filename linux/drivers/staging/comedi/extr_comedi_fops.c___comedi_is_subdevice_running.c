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
struct comedi_subdevice {int dummy; } ;

/* Variables and functions */
 unsigned int __comedi_get_subdevice_runflags (struct comedi_subdevice*) ; 
 int comedi_is_runflags_running (unsigned int) ; 

__attribute__((used)) static bool __comedi_is_subdevice_running(struct comedi_subdevice *s)
{
	unsigned int runflags = __comedi_get_subdevice_runflags(s);

	return comedi_is_runflags_running(runflags);
}