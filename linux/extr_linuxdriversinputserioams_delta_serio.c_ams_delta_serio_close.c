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
struct serio {struct ams_delta_serio* port_data; } ;
struct ams_delta_serio {int /*<<< orphan*/  vcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ams_delta_serio_close(struct serio *serio)
{
	struct ams_delta_serio *priv = serio->port_data;

	/* disable keyboard */
	regulator_disable(priv->vcc);
}