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
struct intel_guc_client {int /*<<< orphan*/  doorbell_id; TYPE_1__* guc; } ;
struct TYPE_2__ {int /*<<< orphan*/  doorbell_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GUC_DOORBELL_INVALID ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_doorbell (struct intel_guc_client*) ; 

__attribute__((used)) static void unreserve_doorbell(struct intel_guc_client *client)
{
	GEM_BUG_ON(!has_doorbell(client));

	__clear_bit(client->doorbell_id, client->guc->doorbell_bitmap);
	client->doorbell_id = GUC_DOORBELL_INVALID;
}