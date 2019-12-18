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
struct nvmf_host {int /*<<< orphan*/  list; int /*<<< orphan*/  nqn; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVMF_NQN_SIZE ; 
 struct nvmf_host* __nvmf_host_find (char const*) ; 
 struct nvmf_host* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmf_hosts ; 
 int /*<<< orphan*/  nvmf_hosts_mutex ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nvmf_host *nvmf_host_add(const char *hostnqn)
{
	struct nvmf_host *host;

	mutex_lock(&nvmf_hosts_mutex);
	host = __nvmf_host_find(hostnqn);
	if (host) {
		kref_get(&host->ref);
		goto out_unlock;
	}

	host = kmalloc(sizeof(*host), GFP_KERNEL);
	if (!host)
		goto out_unlock;

	kref_init(&host->ref);
	strlcpy(host->nqn, hostnqn, NVMF_NQN_SIZE);

	list_add_tail(&host->list, &nvmf_hosts);
out_unlock:
	mutex_unlock(&nvmf_hosts_mutex);
	return host;
}