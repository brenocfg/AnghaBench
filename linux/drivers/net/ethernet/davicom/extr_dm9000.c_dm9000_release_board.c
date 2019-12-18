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
struct platform_device {int dummy; } ;
struct board_info {scalar_t__ addr_req; scalar_t__ data_req; int /*<<< orphan*/  io_data; int /*<<< orphan*/  io_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  release_resource (scalar_t__) ; 

__attribute__((used)) static void
dm9000_release_board(struct platform_device *pdev, struct board_info *db)
{
	/* unmap our resources */

	iounmap(db->io_addr);
	iounmap(db->io_data);

	/* release the resources */

	if (db->data_req)
		release_resource(db->data_req);
	kfree(db->data_req);

	if (db->addr_req)
		release_resource(db->addr_req);
	kfree(db->addr_req);
}