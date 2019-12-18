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
typedef  int /*<<< orphan*/  u8 ;
struct zd_chip {int dummy; } ;

/* Variables and functions */
 int scnprintf (char*,size_t,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_to_mac (struct zd_chip*) ; 
 int /*<<< orphan*/ * zd_mac_get_perm_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scnprint_mac_oui(struct zd_chip *chip, char *buffer, size_t size)
{
	u8 *addr = zd_mac_get_perm_addr(zd_chip_to_mac(chip));
	return scnprintf(buffer, size, "%3phD", addr);
}