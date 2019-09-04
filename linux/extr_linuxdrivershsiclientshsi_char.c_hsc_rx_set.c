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
struct hsi_config {scalar_t__ mode; int num_hw_channels; scalar_t__ flow; } ;
struct hsi_client {struct hsi_config rx_cfg; } ;
struct hsc_rx_config {scalar_t__ mode; int channels; scalar_t__ flow; } ;

/* Variables and functions */
 int EINVAL ; 
 int HSC_DEVS ; 
 scalar_t__ HSI_FLOW_PIPE ; 
 scalar_t__ HSI_FLOW_SYNC ; 
 scalar_t__ HSI_MODE_FRAME ; 
 scalar_t__ HSI_MODE_STREAM ; 
 int /*<<< orphan*/  hsc_break_request (struct hsi_client*) ; 
 int hsi_setup (struct hsi_client*) ; 

__attribute__((used)) static int hsc_rx_set(struct hsi_client *cl, struct hsc_rx_config *rxc)
{
	struct hsi_config tmp;
	int ret;

	if ((rxc->mode != HSI_MODE_STREAM) && (rxc->mode != HSI_MODE_FRAME))
		return -EINVAL;
	if ((rxc->channels == 0) || (rxc->channels > HSC_DEVS))
		return -EINVAL;
	if (rxc->channels & (rxc->channels - 1))
		return -EINVAL;
	if ((rxc->flow != HSI_FLOW_SYNC) && (rxc->flow != HSI_FLOW_PIPE))
		return -EINVAL;
	tmp = cl->rx_cfg;
	cl->rx_cfg.mode = rxc->mode;
	cl->rx_cfg.num_hw_channels = rxc->channels;
	cl->rx_cfg.flow = rxc->flow;
	ret = hsi_setup(cl);
	if (ret < 0) {
		cl->rx_cfg = tmp;
		return ret;
	}
	if (rxc->mode == HSI_MODE_FRAME)
		hsc_break_request(cl);

	return ret;
}