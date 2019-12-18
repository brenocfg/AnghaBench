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
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmw_connector_to_sou (struct drm_connector*) ; 
 int /*<<< orphan*/  vmw_sou_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmw_sou_connector_destroy(struct drm_connector *connector)
{
	vmw_sou_destroy(vmw_connector_to_sou(connector));
}