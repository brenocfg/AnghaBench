#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ sin6_port; } ;
struct TYPE_4__ {scalar_t__ sin_port; } ;
struct cxgbi_sock {size_t port_id; scalar_t__ csk_family; TYPE_2__ saddr6; TYPE_1__ saddr; struct cxgbi_device* cdev; } ;
struct cxgbi_ports_map {int max_connect; int used; int next; int /*<<< orphan*/  lock; scalar_t__ sport_base; struct cxgbi_sock** port_csk; } ;
struct cxgbi_device {TYPE_3__** ports; struct cxgbi_ports_map pmap; } ;
typedef  scalar_t__ __be16 ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int CXGBI_DBG_SOCK ; 
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  cxgbi_sock_get (struct cxgbi_sock*) ; 
 scalar_t__ htons (scalar_t__) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_device*,size_t,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,struct cxgbi_device*,...) ; 
 int /*<<< orphan*/  pr_info (char*,struct cxgbi_device*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,struct cxgbi_device*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sock_get_port(struct cxgbi_sock *csk)
{
	struct cxgbi_device *cdev = csk->cdev;
	struct cxgbi_ports_map *pmap = &cdev->pmap;
	unsigned int start;
	int idx;
	__be16 *port;

	if (!pmap->max_connect) {
		pr_err("cdev 0x%p, p#%u %s, NO port map.\n",
			   cdev, csk->port_id, cdev->ports[csk->port_id]->name);
		return -EADDRNOTAVAIL;
	}

	if (csk->csk_family == AF_INET)
		port = &csk->saddr.sin_port;
	else /* ipv6 */
		port = &csk->saddr6.sin6_port;

	if (*port) {
		pr_err("source port NON-ZERO %u.\n",
			ntohs(*port));
		return -EADDRINUSE;
	}

	spin_lock_bh(&pmap->lock);
	if (pmap->used >= pmap->max_connect) {
		spin_unlock_bh(&pmap->lock);
		pr_info("cdev 0x%p, p#%u %s, ALL ports used.\n",
			cdev, csk->port_id, cdev->ports[csk->port_id]->name);
		return -EADDRNOTAVAIL;
	}

	start = idx = pmap->next;
	do {
		if (++idx >= pmap->max_connect)
			idx = 0;
		if (!pmap->port_csk[idx]) {
			pmap->used++;
			*port = htons(pmap->sport_base + idx);
			pmap->next = idx;
			pmap->port_csk[idx] = csk;
			spin_unlock_bh(&pmap->lock);
			cxgbi_sock_get(csk);
			log_debug(1 << CXGBI_DBG_SOCK,
				"cdev 0x%p, p#%u %s, p %u, %u.\n",
				cdev, csk->port_id,
				cdev->ports[csk->port_id]->name,
				pmap->sport_base + idx, pmap->next);
			return 0;
		}
	} while (idx != start);
	spin_unlock_bh(&pmap->lock);

	/* should not happen */
	pr_warn("cdev 0x%p, p#%u %s, next %u?\n",
		cdev, csk->port_id, cdev->ports[csk->port_id]->name,
		pmap->next);
	return -EADDRNOTAVAIL;
}