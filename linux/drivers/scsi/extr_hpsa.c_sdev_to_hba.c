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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct ctlr_info {int dummy; } ;

/* Variables and functions */
 unsigned long* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ctlr_info *sdev_to_hba(struct scsi_device *sdev)
{
	unsigned long *priv = shost_priv(sdev->host);
	return (struct ctlr_info *) *priv;
}