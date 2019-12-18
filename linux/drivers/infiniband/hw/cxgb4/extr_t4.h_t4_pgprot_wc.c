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
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline pgprot_t t4_pgprot_wc(pgprot_t prot)
{
#if defined(__i386__) || defined(__x86_64__) || defined(CONFIG_PPC64)
	return pgprot_writecombine(prot);
#else
	return pgprot_noncached(prot);
#endif
}