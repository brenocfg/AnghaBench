#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sti_dvo_connector {struct sti_dvo* dvo; } ;
struct sti_dvo {TYPE_2__* panel; } ;
struct drm_connector {int dummy; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct TYPE_3__ {int (* get_modes ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*) ; 
 struct sti_dvo_connector* to_sti_dvo_connector (struct drm_connector*) ; 

__attribute__((used)) static int sti_dvo_connector_get_modes(struct drm_connector *connector)
{
	struct sti_dvo_connector *dvo_connector
		= to_sti_dvo_connector(connector);
	struct sti_dvo *dvo = dvo_connector->dvo;

	if (dvo->panel)
		return dvo->panel->funcs->get_modes(dvo->panel);

	return 0;
}