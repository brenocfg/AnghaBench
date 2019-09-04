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
struct oaktrail_hdmi_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_HICR ; 
 int /*<<< orphan*/  HDMI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_WRITE (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hdmi_i2c_irq_disable(struct oaktrail_hdmi_dev *hdmi_dev)
{
	HDMI_WRITE(HDMI_HICR, 0x0);
	HDMI_READ(HDMI_HICR);
}