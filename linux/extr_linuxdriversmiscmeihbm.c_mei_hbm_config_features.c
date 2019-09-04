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
struct TYPE_2__ {scalar_t__ major_version; scalar_t__ minor_version; } ;
struct mei_device {int hbm_f_pg_supported; int hbm_f_dc_supported; int hbm_f_ie_supported; int hbm_f_dot_supported; int hbm_f_ev_supported; int hbm_f_fa_supported; int hbm_f_os_supported; int hbm_f_dr_supported; TYPE_1__ version; } ;

/* Variables and functions */
 scalar_t__ HBM_MAJOR_VERSION_DC ; 
 scalar_t__ HBM_MAJOR_VERSION_DOT ; 
 scalar_t__ HBM_MAJOR_VERSION_DR ; 
 scalar_t__ HBM_MAJOR_VERSION_EV ; 
 scalar_t__ HBM_MAJOR_VERSION_FA ; 
 scalar_t__ HBM_MAJOR_VERSION_IE ; 
 scalar_t__ HBM_MAJOR_VERSION_OS ; 
 scalar_t__ HBM_MAJOR_VERSION_PGI ; 
 scalar_t__ HBM_MINOR_VERSION_DR ; 
 scalar_t__ HBM_MINOR_VERSION_PGI ; 

__attribute__((used)) static void mei_hbm_config_features(struct mei_device *dev)
{
	/* Power Gating Isolation Support */
	dev->hbm_f_pg_supported = 0;
	if (dev->version.major_version > HBM_MAJOR_VERSION_PGI)
		dev->hbm_f_pg_supported = 1;

	if (dev->version.major_version == HBM_MAJOR_VERSION_PGI &&
	    dev->version.minor_version >= HBM_MINOR_VERSION_PGI)
		dev->hbm_f_pg_supported = 1;

	dev->hbm_f_dc_supported = 0;
	if (dev->version.major_version >= HBM_MAJOR_VERSION_DC)
		dev->hbm_f_dc_supported = 1;

	dev->hbm_f_ie_supported = 0;
	if (dev->version.major_version >= HBM_MAJOR_VERSION_IE)
		dev->hbm_f_ie_supported = 1;

	/* disconnect on connect timeout instead of link reset */
	dev->hbm_f_dot_supported = 0;
	if (dev->version.major_version >= HBM_MAJOR_VERSION_DOT)
		dev->hbm_f_dot_supported = 1;

	/* Notification Event Support */
	dev->hbm_f_ev_supported = 0;
	if (dev->version.major_version >= HBM_MAJOR_VERSION_EV)
		dev->hbm_f_ev_supported = 1;

	/* Fixed Address Client Support */
	dev->hbm_f_fa_supported = 0;
	if (dev->version.major_version >= HBM_MAJOR_VERSION_FA)
		dev->hbm_f_fa_supported = 1;

	/* OS ver message Support */
	dev->hbm_f_os_supported = 0;
	if (dev->version.major_version >= HBM_MAJOR_VERSION_OS)
		dev->hbm_f_os_supported = 1;

	/* DMA Ring Support */
	dev->hbm_f_dr_supported = 0;
	if (dev->version.major_version > HBM_MAJOR_VERSION_DR ||
	    (dev->version.major_version == HBM_MAJOR_VERSION_DR &&
	     dev->version.minor_version >= HBM_MINOR_VERSION_DR))
		dev->hbm_f_dr_supported = 1;
}