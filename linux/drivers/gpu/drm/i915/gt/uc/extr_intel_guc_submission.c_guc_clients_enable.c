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
struct intel_guc {int /*<<< orphan*/  execbuf_client; } ;

/* Variables and functions */
 int __guc_client_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int guc_clients_enable(struct intel_guc *guc)
{
	return __guc_client_enable(guc->execbuf_client);
}