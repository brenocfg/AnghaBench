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
typedef  scalar_t__ u32 ;
struct pcb_config {scalar_t__ config_num; } ;
struct cx231xx {int /*<<< orphan*/  current_pcb_config; } ;

/* Variables and functions */
#define  Audio 134 
 scalar_t__ ENABLE_EP1 ; 
 scalar_t__ ENABLE_EP2 ; 
 scalar_t__ ENABLE_EP3 ; 
 scalar_t__ ENABLE_EP4 ; 
 scalar_t__ ENABLE_EP5 ; 
 scalar_t__ ENABLE_EP6 ; 
#define  Raw_Video 133 
#define  Sliced_cc 132 
#define  TS1_parallel_mode 131 
#define  TS1_serial_mode 130 
#define  TS2 129 
#define  Vbi 128 
 int cx231xx_initialize_stream_xfer (struct cx231xx*,int) ; 
 int cx231xx_start_stream (struct cx231xx*,scalar_t__) ; 
 int cx231xx_stop_stream (struct cx231xx*,scalar_t__) ; 

int cx231xx_capture_start(struct cx231xx *dev, int start, u8 media_type)
{
	int rc = -1;
	u32 ep_mask = -1;
	struct pcb_config *pcb_config;

	/* get EP for media type */
	pcb_config = (struct pcb_config *)&dev->current_pcb_config;

	if (pcb_config->config_num) {
		switch (media_type) {
		case Raw_Video:
			ep_mask = ENABLE_EP4;	/* ep4  [00:1000] */
			break;
		case Audio:
			ep_mask = ENABLE_EP3;	/* ep3  [00:0100] */
			break;
		case Vbi:
			ep_mask = ENABLE_EP5;	/* ep5 [01:0000] */
			break;
		case Sliced_cc:
			ep_mask = ENABLE_EP6;	/* ep6 [10:0000] */
			break;
		case TS1_serial_mode:
		case TS1_parallel_mode:
			ep_mask = ENABLE_EP1;	/* ep1 [00:0001] */
			break;
		case TS2:
			ep_mask = ENABLE_EP2;	/* ep2 [00:0010] */
			break;
		}
	}

	if (start) {
		rc = cx231xx_initialize_stream_xfer(dev, media_type);

		if (rc < 0)
			return rc;

		/* enable video capture */
		if (ep_mask > 0)
			rc = cx231xx_start_stream(dev, ep_mask);
	} else {
		/* disable video capture */
		if (ep_mask > 0)
			rc = cx231xx_stop_stream(dev, ep_mask);
	}

	return rc;
}