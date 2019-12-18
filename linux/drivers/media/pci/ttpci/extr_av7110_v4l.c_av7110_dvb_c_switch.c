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
typedef  int u16 ;
struct saa7146_vv {int video_status; int /*<<< orphan*/ * ov_suspend; int /*<<< orphan*/ * video_fh; } ;
struct saa7146_standard {int dummy; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {scalar_t__ ext_priv; struct saa7146_vv* vv_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;
struct av7110 {int current_input; int analog_tuner_flags; TYPE_1__ dvb_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADSwitch ; 
 int ANALOG_TUNER_STV0297 ; 
 int ANALOG_TUNER_VES1820 ; 
 int /*<<< orphan*/  COMTYPE_AUDIODAC ; 
 int /*<<< orphan*/  MSP_WR_DSP ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTHI ; 
 int /*<<< orphan*/  SAA7146_GPIO_OUTLO ; 
 int SAA7146_HPS_SOURCE_PORT_A ; 
 int SAA7146_HPS_SOURCE_PORT_B ; 
 int SAA7146_HPS_SYNC_PORT_A ; 
 int SAA7146_HPS_SYNC_PORT_B ; 
 int STATUS_OVERLAY ; 
 int /*<<< orphan*/  analog_standard ; 
 scalar_t__ av7110_fw_cmd (struct av7110*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 int /*<<< orphan*/  dvb_standard ; 
 int i2c_writereg (struct av7110*,int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msp_writereg (struct av7110*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  saa7146_set_hps_source_and_sync (struct saa7146_dev*,int,int) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_start_preview (int /*<<< orphan*/ *) ; 
 int saa7146_stop_preview (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  standard ; 
 scalar_t__ ves1820_writereg (struct saa7146_dev*,int,int,int) ; 

__attribute__((used)) static int av7110_dvb_c_switch(struct saa7146_fh *fh)
{
	struct saa7146_dev *dev = fh->dev;
	struct saa7146_vv *vv = dev->vv_data;
	struct av7110 *av7110 = (struct av7110*)dev->ext_priv;
	u16 adswitch;
	int source, sync, err;

	dprintk(4, "%p\n", av7110);

	if ((vv->video_status & STATUS_OVERLAY) != 0) {
		vv->ov_suspend = vv->video_fh;
		err = saa7146_stop_preview(vv->video_fh); /* side effect: video_status is now 0, video_fh is NULL */
		if (err != 0) {
			dprintk(2, "suspending video failed\n");
			vv->ov_suspend = NULL;
		}
	}

	if (0 != av7110->current_input) {
		dprintk(1, "switching to analog TV:\n");
		adswitch = 1;
		source = SAA7146_HPS_SOURCE_PORT_B;
		sync = SAA7146_HPS_SYNC_PORT_B;
		memcpy(standard, analog_standard, sizeof(struct saa7146_standard) * 2);

		switch (av7110->current_input) {
		case 1:
			dprintk(1, "switching SAA7113 to Analog Tuner Input\n");
			msp_writereg(av7110, MSP_WR_DSP, 0x0008, 0x0000); // loudspeaker source
			msp_writereg(av7110, MSP_WR_DSP, 0x0009, 0x0000); // headphone source
			msp_writereg(av7110, MSP_WR_DSP, 0x000a, 0x0000); // SCART 1 source
			msp_writereg(av7110, MSP_WR_DSP, 0x000e, 0x3000); // FM matrix, mono
			msp_writereg(av7110, MSP_WR_DSP, 0x0000, 0x4f00); // loudspeaker + headphone
			msp_writereg(av7110, MSP_WR_DSP, 0x0007, 0x4f00); // SCART 1 volume

			if (av7110->analog_tuner_flags & ANALOG_TUNER_VES1820) {
				if (ves1820_writereg(dev, 0x09, 0x0f, 0x60))
					dprintk(1, "setting band in demodulator failed\n");
			} else if (av7110->analog_tuner_flags & ANALOG_TUNER_STV0297) {
				saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTHI); // TDA9819 pin9(STD)
				saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTHI); // TDA9819 pin30(VIF)
			}
			if (i2c_writereg(av7110, 0x48, 0x02, 0xd0) != 1)
				dprintk(1, "saa7113 write failed @ card %d", av7110->dvb_adapter.num);
			break;
		case 2:
			dprintk(1, "switching SAA7113 to Video AV CVBS Input\n");
			if (i2c_writereg(av7110, 0x48, 0x02, 0xd2) != 1)
				dprintk(1, "saa7113 write failed @ card %d", av7110->dvb_adapter.num);
			break;
		case 3:
			dprintk(1, "switching SAA7113 to Video AV Y/C Input\n");
			if (i2c_writereg(av7110, 0x48, 0x02, 0xd9) != 1)
				dprintk(1, "saa7113 write failed @ card %d", av7110->dvb_adapter.num);
			break;
		default:
			dprintk(1, "switching SAA7113 to Input: AV7110: SAA7113: invalid input\n");
		}
	} else {
		adswitch = 0;
		source = SAA7146_HPS_SOURCE_PORT_A;
		sync = SAA7146_HPS_SYNC_PORT_A;
		memcpy(standard, dvb_standard, sizeof(struct saa7146_standard) * 2);
		dprintk(1, "switching DVB mode\n");
		msp_writereg(av7110, MSP_WR_DSP, 0x0008, 0x0220); // loudspeaker source
		msp_writereg(av7110, MSP_WR_DSP, 0x0009, 0x0220); // headphone source
		msp_writereg(av7110, MSP_WR_DSP, 0x000a, 0x0220); // SCART 1 source
		msp_writereg(av7110, MSP_WR_DSP, 0x000e, 0x3000); // FM matrix, mono
		msp_writereg(av7110, MSP_WR_DSP, 0x0000, 0x7f00); // loudspeaker + headphone
		msp_writereg(av7110, MSP_WR_DSP, 0x0007, 0x7f00); // SCART 1 volume

		if (av7110->analog_tuner_flags & ANALOG_TUNER_VES1820) {
			if (ves1820_writereg(dev, 0x09, 0x0f, 0x20))
				dprintk(1, "setting band in demodulator failed\n");
		} else if (av7110->analog_tuner_flags & ANALOG_TUNER_STV0297) {
			saa7146_setgpio(dev, 1, SAA7146_GPIO_OUTLO); // TDA9819 pin9(STD)
			saa7146_setgpio(dev, 3, SAA7146_GPIO_OUTLO); // TDA9819 pin30(VIF)
		}
	}

	/* hmm, this does not do anything!? */
	if (av7110_fw_cmd(av7110, COMTYPE_AUDIODAC, ADSwitch, 1, adswitch))
		dprintk(1, "ADSwitch error\n");

	saa7146_set_hps_source_and_sync(dev, source, sync);

	if (vv->ov_suspend != NULL) {
		saa7146_start_preview(vv->ov_suspend);
		vv->ov_suspend = NULL;
	}

	return 0;
}