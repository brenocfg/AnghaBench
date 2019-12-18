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
struct intel_guc_client {int priority; scalar_t__ doorbell_id; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GUC_DOORBELL_INVALID ; 

__attribute__((used)) static int validate_client(struct intel_guc_client *client, int client_priority)
{
	if (client->priority != client_priority ||
	    client->doorbell_id == GUC_DOORBELL_INVALID)
		return -EINVAL;
	else
		return 0;
}