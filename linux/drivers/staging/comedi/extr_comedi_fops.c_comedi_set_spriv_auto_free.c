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
 int /*<<< orphan*/  COMEDI_SRF_FREE_SPRIV ; 
 int /*<<< orphan*/  __comedi_set_subdevice_runflags (struct comedi_subdevice*,int /*<<< orphan*/ ) ; 

void comedi_set_spriv_auto_free(struct comedi_subdevice *s)
{
	__comedi_set_subdevice_runflags(s, COMEDI_SRF_FREE_SPRIV);
}