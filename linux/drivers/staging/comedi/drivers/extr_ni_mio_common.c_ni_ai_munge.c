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
struct ni_private {scalar_t__* ai_offset; } ;
struct comedi_subdevice {int subdev_flags; struct comedi_async* async; } ;
struct comedi_device {struct ni_private* private; } ;
struct comedi_cmd {unsigned int chanlist_len; } ;
struct comedi_async {struct comedi_cmd cmd; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int SDF_LSAMPL ; 
 unsigned int comedi_bytes_to_samples (struct comedi_subdevice*,unsigned int) ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_ai_munge(struct comedi_device *dev, struct comedi_subdevice *s,
			void *data, unsigned int num_bytes,
			unsigned int chan_index)
{
	struct ni_private *devpriv = dev->private;
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	unsigned int nsamples = comedi_bytes_to_samples(s, num_bytes);
	unsigned short *array = data;
	unsigned int *larray = data;
	unsigned int i;
#ifdef PCIDMA
	__le16 *barray = data;
	__le32 *blarray = data;
#endif

	for (i = 0; i < nsamples; i++) {
#ifdef PCIDMA
		if (s->subdev_flags & SDF_LSAMPL)
			larray[i] = le32_to_cpu(blarray[i]);
		else
			array[i] = le16_to_cpu(barray[i]);
#endif
		if (s->subdev_flags & SDF_LSAMPL)
			larray[i] += devpriv->ai_offset[chan_index];
		else
			array[i] += devpriv->ai_offset[chan_index];
		chan_index++;
		chan_index %= cmd->chanlist_len;
	}
}