#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct saa7146_pci_extension_data {int dummy; } ;
struct TYPE_3__ {int dma_handle; } ;
struct saa7146_dev {struct budget_patch* ext_priv; TYPE_1__ d_rps1; } ;
struct TYPE_4__ {struct budget_patch* priv; } ;
struct budget_patch {int buffer_height; TYPE_2__ dvb_adapter; } ;

/* Variables and functions */
 int CMD_JUMP ; 
 int CMD_PAUSE ; 
 int CMD_STOP ; 
 int CMD_WR_REG_MASK ; 
 int ENOMEM ; 
 int EVT_HS ; 
 int EVT_VBI_B ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIO3_MSK ; 
 int GPIO_CTRL ; 
 int MASK_12 ; 
 int MASK_13 ; 
 int MASK_28 ; 
 int MASK_29 ; 
 int /*<<< orphan*/  MC1 ; 
 int /*<<< orphan*/  RPS_ADDR1 ; 
 int RPS_INV ; 
 int /*<<< orphan*/  RPS_THRESH1 ; 
 int /*<<< orphan*/  RPS_TOV1 ; 
 int SAA7146_GPIO_OUTHI ; 
 int SAA7146_GPIO_OUTLO ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  WRITE_RPS1 (int) ; 
 int /*<<< orphan*/  adapter_nr ; 
 int /*<<< orphan*/  dprintk (int,char*,struct budget_patch*) ; 
 int /*<<< orphan*/  frontend_init (struct budget_patch*) ; 
 int /*<<< orphan*/  kfree (struct budget_patch*) ; 
 struct budget_patch* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int saa7146_read (struct saa7146_dev*,int) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 
 int ttpci_budget_init (struct budget_patch*,struct saa7146_dev*,struct saa7146_pci_extension_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttpci_budget_init_hooks (struct budget_patch*) ; 

__attribute__((used)) static int budget_patch_attach (struct saa7146_dev* dev, struct saa7146_pci_extension_data *info)
{
	struct budget_patch *budget;
	int err;
	int count = 0;
	int detected = 0;

#define PATCH_RESET 0
#define RPS_IRQ 0
#define HPS_SETUP 0
#if PATCH_RESET
	saa7146_write(dev, MC1, MASK_31);
	msleep(40);
#endif
#if HPS_SETUP
	// initialize registers. Better to have it like this
	// than leaving something unconfigured
	saa7146_write(dev, DD1_STREAM_B, 0);
	// port B VSYNC at rising edge
	saa7146_write(dev, DD1_INIT, 0x00000200);  // have this in budget-core too!
	saa7146_write(dev, BRS_CTRL, 0x00000000);  // VBI

	// debi config
	// saa7146_write(dev, DEBI_CONFIG, MASK_30|MASK_28|MASK_18);

	// zero all HPS registers
	saa7146_write(dev, HPS_H_PRESCALE, 0);                  // r68
	saa7146_write(dev, HPS_H_SCALE, 0);                     // r6c
	saa7146_write(dev, BCS_CTRL, 0);                        // r70
	saa7146_write(dev, HPS_V_SCALE, 0);                     // r60
	saa7146_write(dev, HPS_V_GAIN, 0);                      // r64
	saa7146_write(dev, CHROMA_KEY_RANGE, 0);                // r74
	saa7146_write(dev, CLIP_FORMAT_CTRL, 0);                // r78
	// Set HPS prescaler for port B input
	saa7146_write(dev, HPS_CTRL, (1<<30) | (0<<29) | (1<<28) | (0<<12) );
	saa7146_write(dev, MC2,
	  0 * (MASK_08 | MASK_24)  |   // BRS control
	  0 * (MASK_09 | MASK_25)  |   // a
	  0 * (MASK_10 | MASK_26)  |   // b
	  1 * (MASK_06 | MASK_22)  |   // HPS_CTRL1
	  1 * (MASK_05 | MASK_21)  |   // HPS_CTRL2
	  0 * (MASK_01 | MASK_15)      // DEBI
	   );
#endif
	// Disable RPS1 and RPS0
	saa7146_write(dev, MC1, ( MASK_29 | MASK_28));
	// RPS1 timeout disable
	saa7146_write(dev, RPS_TOV1, 0);

	// code for autodetection
	// will wait for VBI_B event (vertical blank at port B)
	// and will reset GPIO3 after VBI_B is detected.
	// (GPIO3 should be raised high by CPU to
	// test if GPIO3 will generate vertical blank signal
	// in budget patch GPIO3 is connected to VSYNC_B
	count = 0;
#if 0
	WRITE_RPS1(CMD_UPLOAD |
	  MASK_10 | MASK_09 | MASK_08 | MASK_06 | MASK_05 | MASK_04 | MASK_03 | MASK_02 );
#endif
	WRITE_RPS1(CMD_PAUSE | EVT_VBI_B);
	WRITE_RPS1(CMD_WR_REG_MASK | (GPIO_CTRL>>2));
	WRITE_RPS1(GPIO3_MSK);
	WRITE_RPS1(SAA7146_GPIO_OUTLO<<24);
#if RPS_IRQ
	// issue RPS1 interrupt to increment counter
	WRITE_RPS1(CMD_INTERRUPT);
	// at least a NOP is neede between two interrupts
	WRITE_RPS1(CMD_NOP);
	// interrupt again
	WRITE_RPS1(CMD_INTERRUPT);
#endif
	WRITE_RPS1(CMD_STOP);

#if RPS_IRQ
	// set event counter 1 source as RPS1 interrupt (0x03)          (rE4 p53)
	// use 0x03 to track RPS1 interrupts - increase by 1 every gpio3 is toggled
	// use 0x15 to track VPE  interrupts - increase by 1 every vpeirq() is called
	saa7146_write(dev, EC1SSR, (0x03<<2) | 3 );
	// set event counter 1 threshold to maximum allowed value        (rEC p55)
	saa7146_write(dev, ECT1R,  0x3fff );
#endif
	// Fix VSYNC level
	saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTLO);
	// Set RPS1 Address register to point to RPS code               (r108 p42)
	saa7146_write(dev, RPS_ADDR1, dev->d_rps1.dma_handle);
	// Enable RPS1,                                                 (rFC p33)
	saa7146_write(dev, MC1, (MASK_13 | MASK_29 ));


	mdelay(50);
	saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTHI);
	mdelay(150);


	if( (saa7146_read(dev, GPIO_CTRL) & 0x10000000) == 0)
		detected = 1;

#if RPS_IRQ
	printk("Event Counter 1 0x%04x\n", saa7146_read(dev, EC1R) & 0x3fff );
#endif
	// Disable RPS1
	saa7146_write(dev, MC1, ( MASK_29 ));

	if(detected == 0)
		printk("budget-patch not detected or saa7146 in non-default state.\n"
		       "try enabling resetting of 7146 with MASK_31 in MC1 register\n");

	else
		printk("BUDGET-PATCH DETECTED.\n");


/*      OLD (Original design by Roberto Deza):
**      This code will setup the SAA7146_RPS1 to generate a square
**      wave on GPIO3, changing when a field (TS_HEIGHT/2 "lines" of
**      TS_WIDTH packets) has been acquired on SAA7146_D1B video port;
**      then, this GPIO3 output which is connected to the D1B_VSYNC
**      input, will trigger the acquisition of the alternate field
**      and so on.
**      Currently, the TT_budget / WinTV_Nova cards have two ICs
**      (74HCT4040, LVC74) for the generation of this VSYNC signal,
**      which seems that can be done perfectly without this :-)).
*/

/*      New design (By Emard)
**      this rps1 code will copy internal HS event to GPIO3 pin.
**      GPIO3 is in budget-patch hardware connected to port B VSYNC

**      HS is an internal event of 7146, accessible with RPS
**      and temporarily raised high every n lines
**      (n in defined in the RPS_THRESH1 counter threshold)
**      I think HS is raised high on the beginning of the n-th line
**      and remains high until this n-th line that triggered
**      it is completely received. When the reception of n-th line
**      ends, HS is lowered.

**      To transmit data over DMA, 7146 needs changing state at
**      port B VSYNC pin. Any changing of port B VSYNC will
**      cause some DMA data transfer, with more or less packets loss.
**      It depends on the phase and frequency of VSYNC and
**      the way of 7146 is instructed to trigger on port B (defined
**      in DD1_INIT register, 3rd nibble from the right valid
**      numbers are 0-7, see datasheet)
**
**      The correct triggering can minimize packet loss,
**      dvbtraffic should give this stable bandwidths:
**        22k transponder = 33814 kbit/s
**      27.5k transponder = 38045 kbit/s
**      by experiment it is found that the best results
**      (stable bandwidths and almost no packet loss)
**      are obtained using DD1_INIT triggering number 2
**      (Va at rising edge of VS Fa = HS x VS-failing forced toggle)
**      and a VSYNC phase that occurs in the middle of DMA transfer
**      (about byte 188*512=96256 in the DMA window).
**
**      Phase of HS is still not clear to me how to control,
**      It just happens to be so. It can be seen if one enables
**      RPS_IRQ and print Event Counter 1 in vpeirq(). Every
**      time RPS_INTERRUPT is called, the Event Counter 1 will
**      increment. That's how the 7146 is programmed to do event
**      counting in this budget-patch.c
**      I *think* HPS setting has something to do with the phase
**      of HS but I can't be 100% sure in that.

**      hardware debug note: a working budget card (including budget patch)
**      with vpeirq() interrupt setup in mode "0x90" (every 64K) will
**      generate 3 interrupts per 25-Hz DMA frame of 2*188*512 bytes
**      and that means 3*25=75 Hz of interrupt frequency, as seen by
**      watch cat /proc/interrupts
**
**      If this frequency is 3x lower (and data received in the DMA
**      buffer don't start with 0x47, but in the middle of packets,
**      whose lengths appear to be like 188 292 188 104 etc.
**      this means VSYNC line is not connected in the hardware.
**      (check soldering pcb and pins)
**      The same behaviour of missing VSYNC can be duplicated on budget
**      cards, by setting DD1_INIT trigger mode 7 in 3rd nibble.
*/

	// Setup RPS1 "program" (p35)
	count = 0;


	// Wait Source Line Counter Threshold                           (p36)
	WRITE_RPS1(CMD_PAUSE | EVT_HS);
	// Set GPIO3=1                                                  (p42)
	WRITE_RPS1(CMD_WR_REG_MASK | (GPIO_CTRL>>2));
	WRITE_RPS1(GPIO3_MSK);
	WRITE_RPS1(SAA7146_GPIO_OUTHI<<24);
#if RPS_IRQ
	// issue RPS1 interrupt
	WRITE_RPS1(CMD_INTERRUPT);
#endif
	// Wait reset Source Line Counter Threshold                     (p36)
	WRITE_RPS1(CMD_PAUSE | RPS_INV | EVT_HS);
	// Set GPIO3=0                                                  (p42)
	WRITE_RPS1(CMD_WR_REG_MASK | (GPIO_CTRL>>2));
	WRITE_RPS1(GPIO3_MSK);
	WRITE_RPS1(SAA7146_GPIO_OUTLO<<24);
#if RPS_IRQ
	// issue RPS1 interrupt
	WRITE_RPS1(CMD_INTERRUPT);
#endif
	// Jump to begin of RPS program                                 (p37)
	WRITE_RPS1(CMD_JUMP);
	WRITE_RPS1(dev->d_rps1.dma_handle);

	// Fix VSYNC level
	saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTLO);
	// Set RPS1 Address register to point to RPS code               (r108 p42)
	saa7146_write(dev, RPS_ADDR1, dev->d_rps1.dma_handle);

	if (!(budget = kmalloc (sizeof(struct budget_patch), GFP_KERNEL)))
		return -ENOMEM;

	dprintk(2, "budget: %p\n", budget);

	err = ttpci_budget_init(budget, dev, info, THIS_MODULE, adapter_nr);
	if (err) {
		kfree(budget);
		return err;
	}

	// Set Source Line Counter Threshold, using BRS                 (rCC p43)
	// It generates HS event every TS_HEIGHT lines
	// this is related to TS_WIDTH set in register
	// NUM_LINE_BYTE3 in budget-core.c. If NUM_LINE_BYTE
	// low 16 bits are set to TS_WIDTH bytes (TS_WIDTH=2*188
	//,then RPS_THRESH1
	// should be set to trigger every TS_HEIGHT (512) lines.
	//
	saa7146_write(dev, RPS_THRESH1, budget->buffer_height | MASK_12 );

	// saa7146_write(dev, RPS_THRESH0, ((TS_HEIGHT/2)<<16) |MASK_28| (TS_HEIGHT/2) |MASK_12 );
	// Enable RPS1                                                  (rFC p33)
	saa7146_write(dev, MC1, (MASK_13 | MASK_29));


	dev->ext_priv = budget;

	budget->dvb_adapter.priv = budget;
	frontend_init(budget);

	ttpci_budget_init_hooks(budget);

	return 0;
}