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
struct resource_info {int /*<<< orphan*/  res_susp_fen; int /*<<< orphan*/  res_susp_nod; int /*<<< orphan*/  res_susp; int /*<<< orphan*/  res_role; } ;
struct drbd_resource {int /*<<< orphan*/  susp_fen; int /*<<< orphan*/  susp_nod; int /*<<< orphan*/  susp; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn_highest_role (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_connection (struct drbd_resource*) ; 

__attribute__((used)) static void resource_to_info(struct resource_info *info,
			     struct drbd_resource *resource)
{
	info->res_role = conn_highest_role(first_connection(resource));
	info->res_susp = resource->susp;
	info->res_susp_nod = resource->susp_nod;
	info->res_susp_fen = resource->susp_fen;
}