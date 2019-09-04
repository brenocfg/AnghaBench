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
struct smsdvb_client_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_smsdvb_clientslock ; 
 int /*<<< orphan*/  kmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsdvb_unregister_client (struct smsdvb_client_t*) ; 

__attribute__((used)) static void smsdvb_onremove(void *context)
{
	kmutex_lock(&g_smsdvb_clientslock);

	smsdvb_unregister_client((struct smsdvb_client_t *) context);

	kmutex_unlock(&g_smsdvb_clientslock);
}