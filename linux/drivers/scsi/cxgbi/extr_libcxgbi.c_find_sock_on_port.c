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
struct cxgbi_sock {unsigned char port_id; } ;
struct cxgbi_ports_map {unsigned int max_connect; unsigned int used; int /*<<< orphan*/  lock; struct cxgbi_sock** port_csk; } ;
struct cxgbi_device {struct cxgbi_ports_map pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cxgbi_sock *find_sock_on_port(struct cxgbi_device *cdev,
					    unsigned char port_id)
{
	struct cxgbi_ports_map *pmap = &cdev->pmap;
	unsigned int i;
	unsigned int used;

	if (!pmap->max_connect || !pmap->used)
		return NULL;

	spin_lock_bh(&pmap->lock);
	used = pmap->used;
	for (i = 0; used && i < pmap->max_connect; i++) {
		struct cxgbi_sock *csk = pmap->port_csk[i];

		if (csk) {
			if (csk->port_id == port_id) {
				spin_unlock_bh(&pmap->lock);
				return csk;
			}
			used--;
		}
	}
	spin_unlock_bh(&pmap->lock);

	return NULL;
}