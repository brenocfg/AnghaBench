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
struct qib_diag_client {struct qib_diag_client* next; scalar_t__ pid; struct qib_devdata* dd; int /*<<< orphan*/  state; } ;
struct qib_devdata {struct qib_diag_client* diag_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED ; 
 struct qib_diag_client* client_pool ; 

__attribute__((used)) static void return_client(struct qib_diag_client *dc)
{
	struct qib_devdata *dd = dc->dd;
	struct qib_diag_client *tdc, *rdc;

	rdc = NULL;
	if (dc == dd->diag_client) {
		dd->diag_client = dc->next;
		rdc = dc;
	} else {
		tdc = dc->dd->diag_client;
		while (tdc) {
			if (dc == tdc->next) {
				tdc->next = dc->next;
				rdc = dc;
				break;
			}
			tdc = tdc->next;
		}
	}
	if (rdc) {
		rdc->state = UNUSED;
		rdc->dd = NULL;
		rdc->pid = 0;
		rdc->next = client_pool;
		client_pool = rdc;
	}
}