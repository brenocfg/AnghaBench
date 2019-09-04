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
struct cxgbi_ppm {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppm_destroy ; 

int cxgbi_ppm_release(struct cxgbi_ppm *ppm)
{
	if (ppm) {
		int rv;

		rv = kref_put(&ppm->refcnt, ppm_destroy);
		return rv;
	}
	return 1;
}