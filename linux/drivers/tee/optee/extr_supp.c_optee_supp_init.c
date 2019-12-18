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
struct optee_supp {int req_id; int /*<<< orphan*/  reqs; int /*<<< orphan*/  idr; int /*<<< orphan*/  reqs_c; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct optee_supp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void optee_supp_init(struct optee_supp *supp)
{
	memset(supp, 0, sizeof(*supp));
	mutex_init(&supp->mutex);
	init_completion(&supp->reqs_c);
	idr_init(&supp->idr);
	INIT_LIST_HEAD(&supp->reqs);
	supp->req_id = -1;
}