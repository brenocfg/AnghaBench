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
 int /*<<< orphan*/  ASR_CIP ; 
 int /*<<< orphan*/  SBIC_CMND ; 
 scalar_t__ acornscsi_sbic_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  sbic_arm_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
int acornscsi_sbic_issuecmd(AS_Host *host, int command)
{
    if (acornscsi_sbic_wait(host, ASR_CIP, 0, 1000, "issuing command"))
	return -1;

    sbic_arm_write(host, SBIC_CMND, command);

    return 0;
}