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
struct journal_completion {int dummy; } ;
struct dm_integrity_c {scalar_t__ journal_xor; } ;

/* Variables and functions */
 void crypt_journal (struct dm_integrity_c*,int,unsigned int,unsigned int,struct journal_completion*) ; 
 void xor_journal (struct dm_integrity_c*,int,unsigned int,unsigned int,struct journal_completion*) ; 

__attribute__((used)) static void encrypt_journal(struct dm_integrity_c *ic, bool encrypt, unsigned section,
			    unsigned n_sections, struct journal_completion *comp)
{
	if (ic->journal_xor)
		return xor_journal(ic, encrypt, section, n_sections, comp);
	else
		return crypt_journal(ic, encrypt, section, n_sections, comp);
}