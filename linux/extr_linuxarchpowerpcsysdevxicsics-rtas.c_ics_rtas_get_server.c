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
struct ics {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibm_get_xive ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int*,unsigned long) ; 

__attribute__((used)) static long ics_rtas_get_server(struct ics *ics, unsigned long vec)
{
	int rc, status[2];

	rc = rtas_call(ibm_get_xive, 1, 3, status, vec);
	if (rc)
		return -1;
	return status[0];
}