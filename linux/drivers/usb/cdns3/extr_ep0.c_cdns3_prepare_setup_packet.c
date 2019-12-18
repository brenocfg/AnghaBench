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
struct usb_ctrlrequest {int dummy; } ;
struct cdns3_device {int /*<<< orphan*/  setup_dma; int /*<<< orphan*/  ep0_stage; scalar_t__ ep0_data_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS3_SETUP_STAGE ; 
 int /*<<< orphan*/  cdns3_ep0_run_transfer (struct cdns3_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdns3_prepare_setup_packet(struct cdns3_device *priv_dev)
{
	priv_dev->ep0_data_dir = 0;
	priv_dev->ep0_stage = CDNS3_SETUP_STAGE;
	cdns3_ep0_run_transfer(priv_dev, priv_dev->setup_dma,
			       sizeof(struct usb_ctrlrequest), 0, 0);
}