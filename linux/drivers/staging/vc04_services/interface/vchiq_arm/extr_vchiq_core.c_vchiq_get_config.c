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
struct vchiq_config {int /*<<< orphan*/  version_min; int /*<<< orphan*/  version; int /*<<< orphan*/  max_services; int /*<<< orphan*/  max_outstanding_bulks; void* bulk_threshold; void* max_msg_size; } ;

/* Variables and functions */
 void* VCHIQ_MAX_MSG_SIZE ; 
 int /*<<< orphan*/  VCHIQ_MAX_SERVICES ; 
 int /*<<< orphan*/  VCHIQ_NUM_SERVICE_BULKS ; 
 int /*<<< orphan*/  VCHIQ_VERSION ; 
 int /*<<< orphan*/  VCHIQ_VERSION_MIN ; 

void vchiq_get_config(struct vchiq_config *config)
{
	config->max_msg_size           = VCHIQ_MAX_MSG_SIZE;
	config->bulk_threshold         = VCHIQ_MAX_MSG_SIZE;
	config->max_outstanding_bulks  = VCHIQ_NUM_SERVICE_BULKS;
	config->max_services           = VCHIQ_MAX_SERVICES;
	config->version                = VCHIQ_VERSION;
	config->version_min            = VCHIQ_VERSION_MIN;
}