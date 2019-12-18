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
struct mipi_dsi_host_ops {int dummy; } ;
struct mipi_dsi_device {TYPE_1__* host; } ;
struct TYPE_2__ {struct mipi_dsi_host_ops const* ops; } ;
struct intel_dsi_host {int port; struct mipi_dsi_device* device; TYPE_1__ base; struct intel_dsi* intel_dsi; } ;
struct intel_dsi {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct intel_dsi_host*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

struct intel_dsi_host *intel_dsi_host_init(struct intel_dsi *intel_dsi,
					   const struct mipi_dsi_host_ops *funcs,
					   enum port port)
{
	struct intel_dsi_host *host;
	struct mipi_dsi_device *device;

	host = kzalloc(sizeof(*host), GFP_KERNEL);
	if (!host)
		return NULL;

	host->base.ops = funcs;
	host->intel_dsi = intel_dsi;
	host->port = port;

	/*
	 * We should call mipi_dsi_host_register(&host->base) here, but we don't
	 * have a host->dev, and we don't have OF stuff either. So just use the
	 * dsi framework as a library and hope for the best. Create the dsi
	 * devices by ourselves here too. Need to be careful though, because we
	 * don't initialize any of the driver model devices here.
	 */
	device = kzalloc(sizeof(*device), GFP_KERNEL);
	if (!device) {
		kfree(host);
		return NULL;
	}

	device->host = &host->base;
	host->device = device;

	return host;
}