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
struct comedi_insn {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS ; 
 unsigned int NSEC_PER_USEC ; 
 unsigned int TRIG_FOLLOW ; 
 unsigned int TRIG_TIMER ; 

__attribute__((used)) static int waveform_ai_insn_config(struct comedi_device *dev,
				   struct comedi_subdevice *s,
				   struct comedi_insn *insn,
				   unsigned int *data)
{
	if (data[0] == INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS) {
		/*
		 * input:  data[1], data[2] : scan_begin_src, convert_src
		 * output: data[1], data[2] : scan_begin_min, convert_min
		 */
		if (data[1] == TRIG_FOLLOW) {
			/* exactly TRIG_FOLLOW case */
			data[1] = 0;
			data[2] = NSEC_PER_USEC;
		} else {
			data[1] = NSEC_PER_USEC;
			if (data[2] & TRIG_TIMER)
				data[2] = NSEC_PER_USEC;
			else
				data[2] = 0;
		}
		return 0;
	}

	return -EINVAL;
}