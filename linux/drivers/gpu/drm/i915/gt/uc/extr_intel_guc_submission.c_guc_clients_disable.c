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
struct intel_guc {scalar_t__ execbuf_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  __guc_client_disable (scalar_t__) ; 

__attribute__((used)) static void guc_clients_disable(struct intel_guc *guc)
{
	if (guc->execbuf_client)
		__guc_client_disable(guc->execbuf_client);
}