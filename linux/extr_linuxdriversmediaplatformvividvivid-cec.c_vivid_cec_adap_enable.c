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
struct cec_adapter {int cec_pin_is_high; } ;

/* Variables and functions */

__attribute__((used)) static int vivid_cec_adap_enable(struct cec_adapter *adap, bool enable)
{
	adap->cec_pin_is_high = true;
	return 0;
}