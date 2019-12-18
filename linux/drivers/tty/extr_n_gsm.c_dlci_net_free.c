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
struct gsm_dlci {int /*<<< orphan*/ * net; int /*<<< orphan*/  prev_data; int /*<<< orphan*/  data; int /*<<< orphan*/  prev_adaption; int /*<<< orphan*/  adaption; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlci_net_free(struct gsm_dlci *dlci)
{
	if (!dlci->net) {
		WARN_ON(1);
		return;
	}
	dlci->adaption = dlci->prev_adaption;
	dlci->data = dlci->prev_data;
	free_netdev(dlci->net);
	dlci->net = NULL;
}