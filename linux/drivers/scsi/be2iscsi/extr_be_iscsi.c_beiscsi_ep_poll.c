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
struct iscsi_endpoint {struct beiscsi_endpoint* dd_data; } ;
struct beiscsi_endpoint {int cid_vld; int /*<<< orphan*/  phba; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int beiscsi_ep_poll(struct iscsi_endpoint *ep, int timeout_ms)
{
	struct beiscsi_endpoint *beiscsi_ep = ep->dd_data;

	beiscsi_log(beiscsi_ep->phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : In  beiscsi_ep_poll\n");

	if (beiscsi_ep->cid_vld == 1)
		return 1;
	else
		return 0;
}