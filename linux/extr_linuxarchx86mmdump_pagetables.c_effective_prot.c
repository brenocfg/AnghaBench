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
typedef  int pgprotval_t ;

/* Variables and functions */
 int _PAGE_NX ; 
 int _PAGE_RW ; 
 int _PAGE_USER ; 

__attribute__((used)) static inline pgprotval_t effective_prot(pgprotval_t prot1, pgprotval_t prot2)
{
	return (prot1 & prot2 & (_PAGE_USER | _PAGE_RW)) |
	       ((prot1 | prot2) & _PAGE_NX);
}