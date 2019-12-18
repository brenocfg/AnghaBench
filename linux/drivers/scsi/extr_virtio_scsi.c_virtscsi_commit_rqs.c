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
typedef  size_t u16 ;
struct virtio_scsi {int /*<<< orphan*/ * req_vqs; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 struct virtio_scsi* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  virtscsi_kick_vq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtscsi_commit_rqs(struct Scsi_Host *shost, u16 hwq)
{
	struct virtio_scsi *vscsi = shost_priv(shost);

	virtscsi_kick_vq(&vscsi->req_vqs[hwq]);
}