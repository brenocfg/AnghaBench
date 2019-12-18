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
struct nvkm_conn {int /*<<< orphan*/  hpd; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvkm_conn*) ; 
 int /*<<< orphan*/  nvkm_notify_fini (int /*<<< orphan*/ *) ; 

void
nvkm_conn_del(struct nvkm_conn **pconn)
{
	struct nvkm_conn *conn = *pconn;
	if (conn) {
		nvkm_notify_fini(&conn->hpd);
		kfree(*pconn);
		*pconn = NULL;
	}
}