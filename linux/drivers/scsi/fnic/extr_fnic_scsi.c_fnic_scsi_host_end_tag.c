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
struct scsi_cmnd {scalar_t__ host_scribble; } ;
struct request {int dummy; } ;
struct fnic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_request (struct request*) ; 

__attribute__((used)) static inline void
fnic_scsi_host_end_tag(struct fnic *fnic, struct scsi_cmnd *sc)
{
	struct request *dummy = (struct request *)sc->host_scribble;

	blk_mq_free_request(dummy);
}