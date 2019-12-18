#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  port_csk; scalar_t__ max_connect; } ;
struct cxgbi_device {TYPE_1__ pmap; int /*<<< orphan*/  (* cdev2ppm ) (struct cxgbi_device*) ;int /*<<< orphan*/  nports; } ;

/* Variables and functions */
 int CXGBI_DBG_DEV ; 
 int /*<<< orphan*/  cxgbi_device_portmap_cleanup (struct cxgbi_device*) ; 
 int /*<<< orphan*/  cxgbi_free_big_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_hbas_remove (struct cxgbi_device*) ; 
 int /*<<< orphan*/  cxgbi_ppm_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cxgbi_device*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cxgbi_device*) ; 

__attribute__((used)) static inline void cxgbi_device_destroy(struct cxgbi_device *cdev)
{
	log_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p# %u.\n", cdev, cdev->nports);
	cxgbi_hbas_remove(cdev);
	cxgbi_device_portmap_cleanup(cdev);
	cxgbi_ppm_release(cdev->cdev2ppm(cdev));
	if (cdev->pmap.max_connect)
		cxgbi_free_big_mem(cdev->pmap.port_csk);
	kfree(cdev);
}