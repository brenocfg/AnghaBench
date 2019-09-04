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
struct scif_peer_dev {size_t dnode; } ;
struct scif_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct scif_peer_dev* dev_to_scif_peer (struct device*) ; 
 int /*<<< orphan*/  kfree (struct scif_peer_dev*) ; 
 int /*<<< orphan*/  scif_cleanup_scifdev (struct scif_dev*) ; 
 struct scif_dev* scif_dev ; 

__attribute__((used)) static void scif_peer_release_dev(struct device *d)
{
	struct scif_peer_dev *sdev = dev_to_scif_peer(d);
	struct scif_dev *scifdev = &scif_dev[sdev->dnode];

	scif_cleanup_scifdev(scifdev);
	kfree(sdev);
}