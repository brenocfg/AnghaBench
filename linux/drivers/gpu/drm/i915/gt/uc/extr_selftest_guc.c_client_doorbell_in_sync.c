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
struct intel_guc_client {int /*<<< orphan*/  doorbell_id; int /*<<< orphan*/  guc; } ;

/* Variables and functions */
 scalar_t__ doorbell_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool client_doorbell_in_sync(struct intel_guc_client *client)
{
	return !client || doorbell_ok(client->guc, client->doorbell_id);
}