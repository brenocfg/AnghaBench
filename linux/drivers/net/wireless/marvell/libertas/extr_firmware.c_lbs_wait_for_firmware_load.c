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
struct lbs_private {int /*<<< orphan*/ * fw_callback; int /*<<< orphan*/  fw_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lbs_wait_for_firmware_load(struct lbs_private *priv)
{
	wait_event(priv->fw_waitq, priv->fw_callback == NULL);
}