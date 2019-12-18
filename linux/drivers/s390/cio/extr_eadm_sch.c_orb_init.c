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
struct TYPE_2__ {int compat1; int compat2; int fmt; int x; } ;
union orb {TYPE_1__ eadm; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (union orb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void orb_init(union orb *orb)
{
	memset(orb, 0, sizeof(union orb));
	orb->eadm.compat1 = 1;
	orb->eadm.compat2 = 1;
	orb->eadm.fmt = 1;
	orb->eadm.x = 1;
}