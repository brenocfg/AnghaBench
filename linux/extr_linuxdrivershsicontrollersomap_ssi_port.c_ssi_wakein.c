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
struct omap_ssi_port {int /*<<< orphan*/  wake_gpio; } ;
struct hsi_port {int dummy; } ;

/* Variables and functions */
 unsigned int gpiod_get_value (int /*<<< orphan*/ ) ; 
 struct omap_ssi_port* hsi_port_drvdata (struct hsi_port*) ; 

__attribute__((used)) static inline unsigned int ssi_wakein(struct hsi_port *port)
{
	struct omap_ssi_port *omap_port = hsi_port_drvdata(port);
	return gpiod_get_value(omap_port->wake_gpio);
}