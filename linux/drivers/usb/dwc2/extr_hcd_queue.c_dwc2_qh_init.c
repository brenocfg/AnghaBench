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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct dwc2_tt {TYPE_1__* usb_tt; } ;
struct TYPE_4__ {int /*<<< orphan*/ * function; } ;
struct dwc2_qh {int ep_is_in; int maxp; int maxp_mult; int do_split; int dev_speed; int host_interval; int num_hs_transfers; scalar_t__ schedule_low_speed; int /*<<< orphan*/  device_interval; void* device_us; void* host_us; scalar_t__ ep_type; struct dwc2_tt* dwc_tt; int /*<<< orphan*/  ttport; int /*<<< orphan*/  qh_list_entry; int /*<<< orphan*/  qtd_list; int /*<<< orphan*/  data_toggle; TYPE_2__ wait_timer; int /*<<< orphan*/  unreserve_timer; struct dwc2_hsotg* hsotg; } ;
struct dwc2_hsotg {int dummy; } ;
struct dwc2_hcd_urb {int interval; int /*<<< orphan*/  pipe_info; int /*<<< orphan*/  priv; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {scalar_t__ think_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  DWC2_HC_PID_DATA0 ; 
 int /*<<< orphan*/  HPRT0 ; 
 scalar_t__ HPRT0_SPD_HIGH_SPEED ; 
 scalar_t__ HPRT0_SPD_MASK ; 
 scalar_t__ HPRT0_SPD_SHIFT ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* NS_TO_US (int) ; 
#define  USB_ENDPOINT_XFER_BULK 134 
#define  USB_ENDPOINT_XFER_CONTROL 133 
#define  USB_ENDPOINT_XFER_INT 132 
#define  USB_ENDPOINT_XFER_ISOC 131 
#define  USB_SPEED_FULL 130 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_LOW 128 
 int /*<<< orphan*/  dwc2_get_ls_map (struct dwc2_hsotg*,struct dwc2_qh*) ; 
 int /*<<< orphan*/  dwc2_hcd_get_dev_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc2_hcd_get_ep_num (int /*<<< orphan*/ *) ; 
 int dwc2_hcd_get_maxp (int /*<<< orphan*/ *) ; 
 int dwc2_hcd_get_maxp_mult (int /*<<< orphan*/ *) ; 
 scalar_t__ dwc2_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc2_hcd_is_pipe_in (int /*<<< orphan*/ *) ; 
 int dwc2_host_get_speed (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 struct dwc2_tt* dwc2_host_get_tt_info (struct dwc2_hsotg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dwc2_readl (struct dwc2_hsotg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_sch_dbg (struct dwc2_hsotg*,char*,struct dwc2_qh*,...) ; 
 int /*<<< orphan*/  dwc2_unreserve_timer_fn ; 
 int /*<<< orphan*/  dwc2_wait_timer_fn ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_calc_bus_time (int,int,int,int) ; 

__attribute__((used)) static void dwc2_qh_init(struct dwc2_hsotg *hsotg, struct dwc2_qh *qh,
			 struct dwc2_hcd_urb *urb, gfp_t mem_flags)
{
	int dev_speed = dwc2_host_get_speed(hsotg, urb->priv);
	u8 ep_type = dwc2_hcd_get_pipe_type(&urb->pipe_info);
	bool ep_is_in = !!dwc2_hcd_is_pipe_in(&urb->pipe_info);
	bool ep_is_isoc = (ep_type == USB_ENDPOINT_XFER_ISOC);
	bool ep_is_int = (ep_type == USB_ENDPOINT_XFER_INT);
	u32 hprt = dwc2_readl(hsotg, HPRT0);
	u32 prtspd = (hprt & HPRT0_SPD_MASK) >> HPRT0_SPD_SHIFT;
	bool do_split = (prtspd == HPRT0_SPD_HIGH_SPEED &&
			 dev_speed != USB_SPEED_HIGH);
	int maxp = dwc2_hcd_get_maxp(&urb->pipe_info);
	int maxp_mult = dwc2_hcd_get_maxp_mult(&urb->pipe_info);
	int bytecount = maxp_mult * maxp;
	char *speed, *type;

	/* Initialize QH */
	qh->hsotg = hsotg;
	timer_setup(&qh->unreserve_timer, dwc2_unreserve_timer_fn, 0);
	hrtimer_init(&qh->wait_timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	qh->wait_timer.function = &dwc2_wait_timer_fn;
	qh->ep_type = ep_type;
	qh->ep_is_in = ep_is_in;

	qh->data_toggle = DWC2_HC_PID_DATA0;
	qh->maxp = maxp;
	qh->maxp_mult = maxp_mult;
	INIT_LIST_HEAD(&qh->qtd_list);
	INIT_LIST_HEAD(&qh->qh_list_entry);

	qh->do_split = do_split;
	qh->dev_speed = dev_speed;

	if (ep_is_int || ep_is_isoc) {
		/* Compute scheduling parameters once and save them */
		int host_speed = do_split ? USB_SPEED_HIGH : dev_speed;
		struct dwc2_tt *dwc_tt = dwc2_host_get_tt_info(hsotg, urb->priv,
							       mem_flags,
							       &qh->ttport);
		int device_ns;

		qh->dwc_tt = dwc_tt;

		qh->host_us = NS_TO_US(usb_calc_bus_time(host_speed, ep_is_in,
				       ep_is_isoc, bytecount));
		device_ns = usb_calc_bus_time(dev_speed, ep_is_in,
					      ep_is_isoc, bytecount);

		if (do_split && dwc_tt)
			device_ns += dwc_tt->usb_tt->think_time;
		qh->device_us = NS_TO_US(device_ns);

		qh->device_interval = urb->interval;
		qh->host_interval = urb->interval * (do_split ? 8 : 1);

		/*
		 * Schedule low speed if we're running the host in low or
		 * full speed OR if we've got a "TT" to deal with to access this
		 * device.
		 */
		qh->schedule_low_speed = prtspd != HPRT0_SPD_HIGH_SPEED ||
					 dwc_tt;

		if (do_split) {
			/* We won't know num transfers until we schedule */
			qh->num_hs_transfers = -1;
		} else if (dev_speed == USB_SPEED_HIGH) {
			qh->num_hs_transfers = 1;
		} else {
			qh->num_hs_transfers = 0;
		}

		/* We'll schedule later when we have something to do */
	}

	switch (dev_speed) {
	case USB_SPEED_LOW:
		speed = "low";
		break;
	case USB_SPEED_FULL:
		speed = "full";
		break;
	case USB_SPEED_HIGH:
		speed = "high";
		break;
	default:
		speed = "?";
		break;
	}

	switch (qh->ep_type) {
	case USB_ENDPOINT_XFER_ISOC:
		type = "isochronous";
		break;
	case USB_ENDPOINT_XFER_INT:
		type = "interrupt";
		break;
	case USB_ENDPOINT_XFER_CONTROL:
		type = "control";
		break;
	case USB_ENDPOINT_XFER_BULK:
		type = "bulk";
		break;
	default:
		type = "?";
		break;
	}

	dwc2_sch_dbg(hsotg, "QH=%p Init %s, %s speed, %d bytes:\n", qh, type,
		     speed, bytecount);
	dwc2_sch_dbg(hsotg, "QH=%p ...addr=%d, ep=%d, %s\n", qh,
		     dwc2_hcd_get_dev_addr(&urb->pipe_info),
		     dwc2_hcd_get_ep_num(&urb->pipe_info),
		     ep_is_in ? "IN" : "OUT");
	if (ep_is_int || ep_is_isoc) {
		dwc2_sch_dbg(hsotg,
			     "QH=%p ...duration: host=%d us, device=%d us\n",
			     qh, qh->host_us, qh->device_us);
		dwc2_sch_dbg(hsotg, "QH=%p ...interval: host=%d, device=%d\n",
			     qh, qh->host_interval, qh->device_interval);
		if (qh->schedule_low_speed)
			dwc2_sch_dbg(hsotg, "QH=%p ...low speed schedule=%p\n",
				     qh, dwc2_get_ls_map(hsotg, qh));
	}
}