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
struct r3964_message {int sig_flags; scalar_t__ msg_count; int /*<<< orphan*/ * next_block_to_read; int /*<<< orphan*/ * last_msg; int /*<<< orphan*/ * first_msg; struct r3964_message* next; struct pid* pid; int /*<<< orphan*/  lock; } ;
struct r3964_info {struct r3964_message* firstClient; } ;
struct r3964_client_info {int sig_flags; scalar_t__ msg_count; int /*<<< orphan*/ * next_block_to_read; int /*<<< orphan*/ * last_msg; int /*<<< orphan*/ * first_msg; struct r3964_client_info* next; struct pid* pid; int /*<<< orphan*/  lock; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int R3964_SIG_ALL ; 
 int /*<<< orphan*/  TRACE_M (char*,struct r3964_message*) ; 
 int /*<<< orphan*/  TRACE_PS (char*,int /*<<< orphan*/ ) ; 
 struct r3964_message* findClient (struct r3964_info*,struct pid*) ; 
 struct pid* get_pid (struct pid*) ; 
 int /*<<< orphan*/  kfree (struct r3964_message*) ; 
 struct r3964_message* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_nr (struct pid*) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 struct r3964_message* remove_msg (struct r3964_info*,struct r3964_message*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enable_signals(struct r3964_info *pInfo, struct pid *pid, int arg)
{
	struct r3964_client_info *pClient;
	struct r3964_client_info **ppClient;
	struct r3964_message *pMsg;

	if ((arg & R3964_SIG_ALL) == 0) {
		/* Remove client from client list */
		for (ppClient = &pInfo->firstClient; *ppClient;
		     ppClient = &(*ppClient)->next) {
			pClient = *ppClient;

			if (pClient->pid == pid) {
				TRACE_PS("removing client %d from client list",
					 pid_nr(pid));
				*ppClient = pClient->next;
				while (pClient->msg_count) {
					pMsg = remove_msg(pInfo, pClient);
					if (pMsg) {
						kfree(pMsg);
						TRACE_M("enable_signals - msg "
							"kfree %p", pMsg);
					}
				}
				put_pid(pClient->pid);
				kfree(pClient);
				TRACE_M("enable_signals - kfree %p", pClient);
				return 0;
			}
		}
		return -EINVAL;
	} else {
		pClient = findClient(pInfo, pid);
		if (pClient) {
			/* update signal options */
			pClient->sig_flags = arg;
		} else {
			/* add client to client list */
			pClient = kmalloc(sizeof(struct r3964_client_info),
					GFP_KERNEL);
			TRACE_M("enable_signals - kmalloc %p", pClient);
			if (pClient == NULL)
				return -ENOMEM;

			TRACE_PS("add client %d to client list", pid_nr(pid));
			spin_lock_init(&pClient->lock);
			pClient->sig_flags = arg;
			pClient->pid = get_pid(pid);
			pClient->next = pInfo->firstClient;
			pClient->first_msg = NULL;
			pClient->last_msg = NULL;
			pClient->next_block_to_read = NULL;
			pClient->msg_count = 0;
			pInfo->firstClient = pClient;
		}
	}

	return 0;
}