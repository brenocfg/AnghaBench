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
typedef  int u8 ;
typedef  int u32 ;
struct smi_rc {int* irData; struct rc_dev* rc_dev; struct smi_dev* dev; } ;
struct smi_dev {int dummy; } ;
struct rc_dev {int dummy; } ;
struct ir_raw_event {int /*<<< orphan*/  duration; scalar_t__ pulse; } ;

/* Variables and functions */
 scalar_t__ IR_DATA_BUFFER_BASE ; 
 scalar_t__ IR_Data_Cnt ; 
 scalar_t__ IR_Init_Reg ; 
 int SMI_SAMPLE_IDLEMIN ; 
 int SMI_SAMPLE_PERIOD ; 
 int /*<<< orphan*/  US_TO_NS (int) ; 
 int /*<<< orphan*/  ir_raw_event_handle (struct rc_dev*) ; 
 int /*<<< orphan*/  ir_raw_event_store_with_filter (struct rc_dev*,struct ir_raw_event*) ; 
 int rbIRVld ; 
 int rbIRhighidle ; 
 int /*<<< orphan*/  smi_raw_process (struct rc_dev*,int*,int) ; 
 int smi_read (scalar_t__) ; 
 int /*<<< orphan*/  smi_set (scalar_t__,int) ; 

__attribute__((used)) static void smi_ir_decode(struct smi_rc *ir)
{
	struct smi_dev *dev = ir->dev;
	struct rc_dev *rc_dev = ir->rc_dev;
	u32 dwIRControl, dwIRData;
	u8 index, ucIRCount, readLoop;

	dwIRControl = smi_read(IR_Init_Reg);

	if (dwIRControl & rbIRVld) {
		ucIRCount = (u8) smi_read(IR_Data_Cnt);

		readLoop = ucIRCount/4;
		if (ucIRCount % 4)
			readLoop += 1;
		for (index = 0; index < readLoop; index++) {
			dwIRData = smi_read(IR_DATA_BUFFER_BASE + (index * 4));

			ir->irData[index*4 + 0] = (u8)(dwIRData);
			ir->irData[index*4 + 1] = (u8)(dwIRData >> 8);
			ir->irData[index*4 + 2] = (u8)(dwIRData >> 16);
			ir->irData[index*4 + 3] = (u8)(dwIRData >> 24);
		}
		smi_raw_process(rc_dev, ir->irData, ucIRCount);
		smi_set(IR_Init_Reg, rbIRVld);
	}

	if (dwIRControl & rbIRhighidle) {
		struct ir_raw_event rawir = {};

		rawir.pulse = 0;
		rawir.duration = US_TO_NS(SMI_SAMPLE_PERIOD *
					  SMI_SAMPLE_IDLEMIN);
		ir_raw_event_store_with_filter(rc_dev, &rawir);
		smi_set(IR_Init_Reg, rbIRhighidle);
	}

	ir_raw_event_handle(rc_dev);
}