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
typedef  int /*<<< orphan*/  AS_Host ;

/* Variables and functions */
 int /*<<< orphan*/  acornscsi_dumplogline (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static
void acornscsi_dumplog(AS_Host *host, int target)
{
    do {
	acornscsi_dumplogline(host, target, 0);
	acornscsi_dumplogline(host, target, 1);
	acornscsi_dumplogline(host, target, 2);

	if (target == 8)
	    break;

	target = 8;
    } while (1);
}