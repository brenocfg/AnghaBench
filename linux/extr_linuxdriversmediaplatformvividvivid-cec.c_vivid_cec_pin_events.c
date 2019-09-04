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
struct vivid_dev {int /*<<< orphan*/ * cec_tx_adap; int /*<<< orphan*/  cec_rx_adap; } ;
struct cec_msg {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 unsigned int MAX_OUTPUTS ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  vivid_cec_pin_adap_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cec_msg const*,int) ; 

__attribute__((used)) static void vivid_cec_pin_events(struct vivid_dev *dev,
				 const struct cec_msg *msg, bool nacked)
{
	ktime_t ts = ktime_get();
	unsigned int i;

	vivid_cec_pin_adap_events(dev->cec_rx_adap, ts, msg, nacked);
	for (i = 0; i < MAX_OUTPUTS; i++)
		vivid_cec_pin_adap_events(dev->cec_tx_adap[i], ts, msg, nacked);
}