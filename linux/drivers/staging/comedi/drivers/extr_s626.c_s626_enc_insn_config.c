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
typedef  scalar_t__ u16 ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ S626_CLKENAB_ALWAYS ; 
 int /*<<< orphan*/  S626_CLKENAB_INDEX ; 
 int /*<<< orphan*/  S626_CLKMULT_1X ; 
 int /*<<< orphan*/  S626_CLKPOL_POS ; 
 int /*<<< orphan*/  S626_ENCMODE_COUNTER ; 
 int /*<<< orphan*/  S626_INDXSRC_SOFT ; 
 scalar_t__ S626_LATCHSRC_AB_READ ; 
 int /*<<< orphan*/  S626_LOADSRC_INDX ; 
 scalar_t__ S626_SET_STD_CLKENAB (int /*<<< orphan*/ ) ; 
 scalar_t__ S626_SET_STD_CLKMULT (int /*<<< orphan*/ ) ; 
 scalar_t__ S626_SET_STD_CLKPOL (int /*<<< orphan*/ ) ; 
 scalar_t__ S626_SET_STD_ENCMODE (int /*<<< orphan*/ ) ; 
 scalar_t__ S626_SET_STD_INDXSRC (int /*<<< orphan*/ ) ; 
 scalar_t__ S626_SET_STD_LOADSRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_preload (struct comedi_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  s626_pulse_index (struct comedi_device*,unsigned int) ; 
 int /*<<< orphan*/  s626_set_enable (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  s626_set_latch_source (struct comedi_device*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  s626_set_mode (struct comedi_device*,unsigned int,scalar_t__,int) ; 

__attribute__((used)) static int s626_enc_insn_config(struct comedi_device *dev,
				struct comedi_subdevice *s,
				struct comedi_insn *insn, unsigned int *data)
{
	unsigned int chan = CR_CHAN(insn->chanspec);
	u16 setup =
		/* Preload upon index. */
		S626_SET_STD_LOADSRC(S626_LOADSRC_INDX) |
		/* Disable hardware index. */
		S626_SET_STD_INDXSRC(S626_INDXSRC_SOFT) |
		/* Operating mode is Counter. */
		S626_SET_STD_ENCMODE(S626_ENCMODE_COUNTER) |
		/* Active high clock. */
		S626_SET_STD_CLKPOL(S626_CLKPOL_POS) |
		/* Clock multiplier is 1x. */
		S626_SET_STD_CLKMULT(S626_CLKMULT_1X) |
		/* Enabled by index */
		S626_SET_STD_CLKENAB(S626_CLKENAB_INDEX);
	/* uint16_t disable_int_src = true; */
	/* uint32_t Preloadvalue;              //Counter initial value */
	u16 value_latchsrc = S626_LATCHSRC_AB_READ;
	u16 enab = S626_CLKENAB_ALWAYS;

	/* (data==NULL) ? (Preloadvalue=0) : (Preloadvalue=data[0]); */

	s626_set_mode(dev, chan, setup, true);
	s626_preload(dev, chan, data[0]);
	s626_pulse_index(dev, chan);
	s626_set_latch_source(dev, chan, value_latchsrc);
	s626_set_enable(dev, chan, (enab != 0));

	return insn->n;
}