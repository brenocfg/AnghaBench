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
struct ionic_cq_info {struct ionic_admin_comp* cq_desc; } ;
struct ionic_cq {int /*<<< orphan*/  bound_q; int /*<<< orphan*/  done_color; } ;
struct ionic_admin_comp {int /*<<< orphan*/  comp_index; int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int /*<<< orphan*/  color_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ionic_q_service (int /*<<< orphan*/ ,struct ionic_cq_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ionic_adminq_service(struct ionic_cq *cq,
				 struct ionic_cq_info *cq_info)
{
	struct ionic_admin_comp *comp = cq_info->cq_desc;

	if (!color_match(comp->color, cq->done_color))
		return false;

	ionic_q_service(cq->bound_q, cq_info, le16_to_cpu(comp->comp_index));

	return true;
}