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
 int /*<<< orphan*/  SBIC_TRANSCNTH ; 
 int sbic_arm_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long sbic_arm_readnext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
unsigned long acornscsi_sbic_xfcount(AS_Host *host)
{
    unsigned long length;

    length = sbic_arm_read(host, SBIC_TRANSCNTH) << 16;
    length |= sbic_arm_readnext(host) << 8;
    length |= sbic_arm_readnext(host);

    return length;
}