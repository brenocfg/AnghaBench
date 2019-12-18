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
struct tda998x_priv {int /*<<< orphan*/  edid_delay_active; int /*<<< orphan*/  edid_delay_waitq; } ;

/* Variables and functions */
 int wait_event_killable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tda998x_edid_delay_wait(struct tda998x_priv *priv)
{
	return wait_event_killable(priv->edid_delay_waitq, !priv->edid_delay_active);
}