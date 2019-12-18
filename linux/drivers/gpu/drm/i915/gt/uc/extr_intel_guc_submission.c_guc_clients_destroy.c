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
struct intel_guc_client {int dummy; } ;
struct intel_guc {int /*<<< orphan*/  execbuf_client; } ;

/* Variables and functions */
 struct intel_guc_client* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  guc_client_free (struct intel_guc_client*) ; 

__attribute__((used)) static void guc_clients_destroy(struct intel_guc *guc)
{
	struct intel_guc_client *client;

	client = fetch_and_zero(&guc->execbuf_client);
	if (client)
		guc_client_free(client);
}