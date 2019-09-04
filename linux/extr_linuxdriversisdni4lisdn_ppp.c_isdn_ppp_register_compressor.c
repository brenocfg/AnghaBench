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
struct isdn_ppp_compressor {struct isdn_ppp_compressor* prev; struct isdn_ppp_compressor* next; } ;

/* Variables and functions */
 struct isdn_ppp_compressor* ipc_head ; 

int isdn_ppp_register_compressor(struct isdn_ppp_compressor *ipc)
{
	ipc->next = ipc_head;
	ipc->prev = NULL;
	if (ipc_head) {
		ipc_head->prev = ipc;
	}
	ipc_head = ipc;
	return 0;
}