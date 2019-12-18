#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct pvc_device {scalar_t__ dlci; struct pvc_device* next; } ;
typedef  int /*<<< orphan*/  hdlc_device ;
struct TYPE_2__ {struct pvc_device* first_pvc; } ;

/* Variables and functions */
 TYPE_1__* state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct pvc_device *find_pvc(hdlc_device *hdlc, u16 dlci)
{
	struct pvc_device *pvc = state(hdlc)->first_pvc;

	while (pvc) {
		if (pvc->dlci == dlci)
			return pvc;
		if (pvc->dlci > dlci)
			return NULL; /* the list is sorted */
		pvc = pvc->next;
	}

	return NULL;
}