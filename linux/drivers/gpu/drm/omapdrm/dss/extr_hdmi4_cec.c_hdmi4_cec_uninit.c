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
struct hdmi_core_data {int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 

void hdmi4_cec_uninit(struct hdmi_core_data *core)
{
	cec_unregister_adapter(core->adap);
}