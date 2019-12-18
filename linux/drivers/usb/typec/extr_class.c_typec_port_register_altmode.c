#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct typec_port {int /*<<< orphan*/  dev; } ;
struct typec_mux {int dummy; } ;
struct typec_altmode_desc {int dummy; } ;
typedef  struct typec_mux typec_altmode ;
struct TYPE_2__ {struct typec_mux* mux; } ;

/* Variables and functions */
 struct typec_mux* ERR_CAST (struct typec_mux*) ; 
 scalar_t__ IS_ERR (struct typec_mux*) ; 
 TYPE_1__* to_altmode (struct typec_mux*) ; 
 struct typec_mux* typec_mux_get (int /*<<< orphan*/ *,struct typec_altmode_desc const*) ; 
 int /*<<< orphan*/  typec_mux_put (struct typec_mux*) ; 
 struct typec_mux* typec_register_altmode (int /*<<< orphan*/ *,struct typec_altmode_desc const*) ; 

struct typec_altmode *
typec_port_register_altmode(struct typec_port *port,
			    const struct typec_altmode_desc *desc)
{
	struct typec_altmode *adev;
	struct typec_mux *mux;

	mux = typec_mux_get(&port->dev, desc);
	if (IS_ERR(mux))
		return ERR_CAST(mux);

	adev = typec_register_altmode(&port->dev, desc);
	if (IS_ERR(adev))
		typec_mux_put(mux);
	else
		to_altmode(adev)->mux = mux;

	return adev;
}