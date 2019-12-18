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
struct dwc3_gadget_ep_cmd_params {int dummy; } ;
struct dwc3_ep {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int dwc3_send_gadget_ep_cmd(struct dwc3_ep *dep, unsigned cmd,
		struct dwc3_gadget_ep_cmd_params *params)
{ return 0; }