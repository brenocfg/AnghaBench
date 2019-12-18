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
struct r3964_info {int dummy; } ;
struct r3964_client_info {struct r3964_block_header* next_block_to_read; int /*<<< orphan*/  pid; } ;
struct r3964_block_header {scalar_t__ locks; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_PS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_from_rx_queue (struct r3964_info*,struct r3964_block_header*) ; 

__attribute__((used)) static void remove_client_block(struct r3964_info *pInfo,
				struct r3964_client_info *pClient)
{
	struct r3964_block_header *block;

	TRACE_PS("remove_client_block PID %d", pid_nr(pClient->pid));

	block = pClient->next_block_to_read;
	if (block) {
		block->locks--;
		if (block->locks == 0) {
			remove_from_rx_queue(pInfo, block);
		}
	}
	pClient->next_block_to_read = NULL;
}