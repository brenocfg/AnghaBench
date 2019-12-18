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
struct pxa168_eth_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ADD ; 
 int /*<<< orphan*/  HASH_DELETE ; 
 int /*<<< orphan*/  add_del_hash_entry (struct pxa168_eth_private*,unsigned char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_hash_table_mac_address(struct pxa168_eth_private *pep,
					  unsigned char *oaddr,
					  unsigned char *addr)
{
	/* Delete old entry */
	if (oaddr)
		add_del_hash_entry(pep, oaddr, 1, 0, HASH_DELETE);
	/* Add new entry */
	add_del_hash_entry(pep, addr, 1, 0, HASH_ADD);
}