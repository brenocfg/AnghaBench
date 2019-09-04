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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int _PAGE_USER ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool pmb_prot_valid(pgprot_t prot)
{
	return (pgprot_val(prot) & _PAGE_USER) == 0;
}