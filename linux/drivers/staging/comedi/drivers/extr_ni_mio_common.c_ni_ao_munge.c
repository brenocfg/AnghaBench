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
struct comedi_subdevice {TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {unsigned int chanlist_len; int /*<<< orphan*/ * chanlist; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {struct comedi_cmd cmd; } ;

/* Variables and functions */
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,unsigned int) ; 
 unsigned short comedi_offset_munge (struct comedi_subdevice*,unsigned short) ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned short) ; 

__attribute__((used)) static void ni_ao_munge(struct comedi_device *dev, struct comedi_subdevice *s,
			void *data, unsigned int num_bytes,
			unsigned int chan_index)
{
	struct comedi_cmd *cmd = &s->async->cmd;
	unsigned int nsamples = comedi_bytes_to_samples(s, num_bytes);
	unsigned short *array = data;
	unsigned int i;
#ifdef PCIDMA
	__le16 buf, *barray = data;
#endif

	for (i = 0; i < nsamples; i++) {
		unsigned int range = CR_RANGE(cmd->chanlist[chan_index]);
		unsigned short val = array[i];

		/*
		 * Munge data from unsigned to two's complement for
		 * bipolar ranges.
		 */
		if (comedi_range_is_bipolar(s, range))
			val = comedi_offset_munge(s, val);
#ifdef PCIDMA
		buf = cpu_to_le16(val);
		barray[i] = buf;
#else
		array[i] = val;
#endif
		chan_index++;
		chan_index %= cmd->chanlist_len;
	}
}