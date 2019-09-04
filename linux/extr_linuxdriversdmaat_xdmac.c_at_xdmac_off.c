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
struct at_xdmac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_XDMAC_GD ; 
 int /*<<< orphan*/  AT_XDMAC_GID ; 
 int /*<<< orphan*/  AT_XDMAC_GS ; 
 scalar_t__ at_xdmac_read (struct at_xdmac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at_xdmac_write (struct at_xdmac*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void at_xdmac_off(struct at_xdmac *atxdmac)
{
	at_xdmac_write(atxdmac, AT_XDMAC_GD, -1L);

	/* Wait that all chans are disabled. */
	while (at_xdmac_read(atxdmac, AT_XDMAC_GS))
		cpu_relax();

	at_xdmac_write(atxdmac, AT_XDMAC_GID, -1L);
}