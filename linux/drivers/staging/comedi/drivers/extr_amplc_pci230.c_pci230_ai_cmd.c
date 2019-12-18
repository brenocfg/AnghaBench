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
typedef  int u64 ;
struct pci230_private {scalar_t__ hwver; int adcg; unsigned short adccon; scalar_t__ daqio; scalar_t__ ai_bipolar; } ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {scalar_t__ iobase; int /*<<< orphan*/  pacer; struct pci230_private* private; } ;
struct comedi_cmd {scalar_t__ scan_begin_src; unsigned int chanlist_len; scalar_t__ convert_src; int convert_arg; int scan_end_arg; int scan_begin_arg; scalar_t__ start_src; int /*<<< orphan*/  flags; int /*<<< orphan*/ * chanlist; } ;
struct comedi_async {int /*<<< orphan*/  inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 scalar_t__ AREF_DIFF ; 
 int /*<<< orphan*/  CMDF_ROUND_UP ; 
 scalar_t__ CR_AREF (int /*<<< orphan*/ ) ; 
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 unsigned int CR_RANGE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int /*<<< orphan*/  GAT_GND ; 
 int /*<<< orphan*/  GAT_VCC ; 
 int /*<<< orphan*/  I8254_MODE1 ; 
 int /*<<< orphan*/  I8254_MODE3 ; 
 int /*<<< orphan*/  OWNER_AICMD ; 
 scalar_t__ PCI230_ADCCON ; 
 scalar_t__ PCI230_ADCEN ; 
 scalar_t__ PCI230_ADCG ; 
 unsigned short PCI230_ADC_FIFO_EN ; 
 unsigned short PCI230_ADC_FIFO_RESET ; 
 unsigned short PCI230_ADC_IM_DIF ; 
 unsigned short PCI230_ADC_IM_SE ; 
 unsigned short PCI230_ADC_INT_FIFO_FULL ; 
 unsigned short PCI230_ADC_IR_BIP ; 
 unsigned short PCI230_ADC_IR_UNI ; 
 unsigned short PCI230_ADC_TRIG_Z2CT2 ; 
 scalar_t__ PCI230_ZGAT_SCE ; 
 unsigned int RES_Z2CT0 ; 
 unsigned int RES_Z2CT1 ; 
 unsigned int RES_Z2CT2 ; 
 scalar_t__ TRIG_FOLLOW ; 
 scalar_t__ TRIG_INT ; 
 scalar_t__ TRIG_TIMER ; 
 int /*<<< orphan*/  comedi_8254_set_mode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ comedi_range_is_bipolar (struct comedi_subdevice*,unsigned int) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 unsigned int* pci230_ai_gain ; 
 int /*<<< orphan*/  pci230_ai_inttrig_start ; 
 int /*<<< orphan*/  pci230_ai_start (struct comedi_device*,struct comedi_subdevice*) ; 
 int /*<<< orphan*/  pci230_claim_shared (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci230_ct_setup_ns_mode (struct comedi_device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned char pci230_gat_config (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pci230_ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct pci230_private *devpriv = dev->private;
	unsigned int i, chan, range, diff;
	unsigned int res_mask;
	unsigned short adccon, adcen;
	unsigned char zgat;

	/* Get the command. */
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;

	/*
	 * Determine which shared resources are needed.
	 */
	res_mask = 0;
	/*
	 * Need Z2-CT2 to supply a conversion trigger source at a high
	 * logic level, even if not doing timed conversions.
	 */
	res_mask |= RES_Z2CT2;
	if (cmd->scan_begin_src != TRIG_FOLLOW) {
		/* Using Z2-CT0 monostable to gate Z2-CT2 conversion timer */
		res_mask |= RES_Z2CT0;
		if (cmd->scan_begin_src == TRIG_TIMER) {
			/* Using Z2-CT1 for scan frequency */
			res_mask |= RES_Z2CT1;
		}
	}
	/* Claim resources. */
	if (!pci230_claim_shared(dev, res_mask, OWNER_AICMD))
		return -EBUSY;

	/*
	 * Steps:
	 * - Set channel scan list.
	 * - Set channel gains.
	 * - Enable and reset FIFO, specify uni/bip, se/diff, and set
	 *   start conversion source to point to something at a high logic
	 *   level (we use the output of counter/timer 2 for this purpose.
	 * - PAUSE to allow things to settle down.
	 * - Reset the FIFO again because it needs resetting twice and there
	 *   may have been a false conversion trigger on some versions of
	 *   PCI230/260 due to the start conversion source being set to a
	 *   high logic level.
	 * - Enable ADC FIFO level interrupt.
	 * - Set actual conversion trigger source and FIFO interrupt trigger
	 *   level.
	 * - If convert_src is TRIG_TIMER, set up the timers.
	 */

	adccon = PCI230_ADC_FIFO_EN;
	adcen = 0;

	if (CR_AREF(cmd->chanlist[0]) == AREF_DIFF) {
		/* Differential - all channels must be differential. */
		diff = 1;
		adccon |= PCI230_ADC_IM_DIF;
	} else {
		/* Single ended - all channels must be single-ended. */
		diff = 0;
		adccon |= PCI230_ADC_IM_SE;
	}

	range = CR_RANGE(cmd->chanlist[0]);
	devpriv->ai_bipolar = comedi_range_is_bipolar(s, range);
	if (devpriv->ai_bipolar)
		adccon |= PCI230_ADC_IR_BIP;
	else
		adccon |= PCI230_ADC_IR_UNI;

	for (i = 0; i < cmd->chanlist_len; i++) {
		unsigned int gainshift;

		chan = CR_CHAN(cmd->chanlist[i]);
		range = CR_RANGE(cmd->chanlist[i]);
		if (diff) {
			gainshift = 2 * chan;
			if (devpriv->hwver == 0) {
				/*
				 * Original PCI230/260 expects both inputs of
				 * the differential channel to be enabled.
				 */
				adcen |= 3 << gainshift;
			} else {
				/*
				 * PCI230+/260+ expects only one input of the
				 * differential channel to be enabled.
				 */
				adcen |= 1 << gainshift;
			}
		} else {
			gainshift = chan & ~1;
			adcen |= 1 << chan;
		}
		devpriv->adcg = (devpriv->adcg & ~(3 << gainshift)) |
				(pci230_ai_gain[range] << gainshift);
	}

	/* Set channel scan list. */
	outw(adcen, devpriv->daqio + PCI230_ADCEN);

	/* Set channel gains. */
	outw(devpriv->adcg, devpriv->daqio + PCI230_ADCG);

	/*
	 * Set counter/timer 2 output high for use as the initial start
	 * conversion source.
	 */
	comedi_8254_set_mode(dev->pacer, 2, I8254_MODE1);

	/*
	 * Temporarily use CT2 output as conversion trigger source and
	 * temporarily set FIFO interrupt trigger level to 'full'.
	 */
	adccon |= PCI230_ADC_INT_FIFO_FULL | PCI230_ADC_TRIG_Z2CT2;

	/*
	 * Enable and reset FIFO, specify FIFO trigger level full, specify
	 * uni/bip, se/diff, and temporarily set the start conversion source
	 * to CT2 output.  Note that CT2 output is currently high, and this
	 * will produce a false conversion trigger on some versions of the
	 * PCI230/260, but that will be dealt with later.
	 */
	devpriv->adccon = adccon;
	outw(adccon | PCI230_ADC_FIFO_RESET, devpriv->daqio + PCI230_ADCCON);

	/*
	 * Delay -
	 * Failure to include this will result in the first few channels'-worth
	 * of data being corrupt, normally manifesting itself by large negative
	 * voltages. It seems the board needs time to settle between the first
	 * FIFO reset (above) and the second FIFO reset (below). Setting the
	 * channel gains and scan list _before_ the first FIFO reset also
	 * helps, though only slightly.
	 */
	usleep_range(25, 100);

	/* Reset FIFO again. */
	outw(adccon | PCI230_ADC_FIFO_RESET, devpriv->daqio + PCI230_ADCCON);

	if (cmd->convert_src == TRIG_TIMER) {
		/*
		 * Set up CT2 as conversion timer, but gate it off for now.
		 * Note, counter/timer output 2 can be monitored on the
		 * connector: PCI230 pin 21, PCI260 pin 18.
		 */
		zgat = pci230_gat_config(2, GAT_GND);
		outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
		/* Set counter/timer 2 to the specified conversion period. */
		pci230_ct_setup_ns_mode(dev, 2, I8254_MODE3, cmd->convert_arg,
					cmd->flags);
		if (cmd->scan_begin_src != TRIG_FOLLOW) {
			/*
			 * Set up monostable on CT0 output for scan timing.  A
			 * rising edge on the trigger (gate) input of CT0 will
			 * trigger the monostable, causing its output to go low
			 * for the configured period.  The period depends on
			 * the conversion period and the number of conversions
			 * in the scan.
			 *
			 * Set the trigger high before setting up the
			 * monostable to stop it triggering.  The trigger
			 * source will be changed later.
			 */
			zgat = pci230_gat_config(0, GAT_VCC);
			outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
			pci230_ct_setup_ns_mode(dev, 0, I8254_MODE1,
						((u64)cmd->convert_arg *
						 cmd->scan_end_arg),
						CMDF_ROUND_UP);
			if (cmd->scan_begin_src == TRIG_TIMER) {
				/*
				 * Monostable on CT0 will be triggered by
				 * output of CT1 at configured scan frequency.
				 *
				 * Set up CT1 but gate it off for now.
				 */
				zgat = pci230_gat_config(1, GAT_GND);
				outb(zgat, dev->iobase + PCI230_ZGAT_SCE);
				pci230_ct_setup_ns_mode(dev, 1, I8254_MODE3,
							cmd->scan_begin_arg,
							cmd->flags);
			}
		}
	}

	if (cmd->start_src == TRIG_INT)
		s->async->inttrig = pci230_ai_inttrig_start;
	else	/* TRIG_NOW */
		pci230_ai_start(dev, s);

	return 0;
}