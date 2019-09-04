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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dn {int dummy; } ;

/* Variables and functions */
 int rtas_write_config (struct pci_dn*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pseries_eeh_write_config(struct pci_dn *pdn, int where, int size, u32 val)
{
	return rtas_write_config(pdn, where, size, val);
}