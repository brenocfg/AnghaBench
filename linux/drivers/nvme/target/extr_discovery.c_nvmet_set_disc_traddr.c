#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvmet_req {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  traddr; } ;
struct nvmet_port {TYPE_2__ disc_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* disc_traddr ) (struct nvmet_req*,struct nvmet_port*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NVMF_TRADDR_SIZE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nvmet_req*,struct nvmet_port*,char*) ; 

__attribute__((used)) static void nvmet_set_disc_traddr(struct nvmet_req *req, struct nvmet_port *port,
		char *traddr)
{
	if (req->ops->disc_traddr)
		req->ops->disc_traddr(req, port, traddr);
	else
		memcpy(traddr, port->disc_addr.traddr, NVMF_TRADDR_SIZE);
}