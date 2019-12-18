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
struct intel_guc_client {scalar_t__ priority; } ;

/* Variables and functions */
 scalar_t__ GUC_CLIENT_PRIORITY_HIGH ; 
 scalar_t__ GUC_CLIENT_PRIORITY_KMD_HIGH ; 

__attribute__((used)) static inline bool is_high_priority(struct intel_guc_client *client)
{
	return (client->priority == GUC_CLIENT_PRIORITY_KMD_HIGH ||
		client->priority == GUC_CLIENT_PRIORITY_HIGH);
}