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
struct Scsi_Host {int /*<<< orphan*/  tag_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 

void scsi_mq_destroy_tags(struct Scsi_Host *shost)
{
	blk_mq_free_tag_set(&shost->tag_set);
}