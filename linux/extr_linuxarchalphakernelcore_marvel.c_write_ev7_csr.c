#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long csr; } ;
typedef  TYPE_1__ ev7_csr ;

/* Variables and functions */
 TYPE_1__* EV7_CSR_KERN (int,unsigned long) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void __attribute__ ((unused))
write_ev7_csr(int pe, unsigned long offset, unsigned long q)
{
	ev7_csr *ev7csr = EV7_CSR_KERN(pe, offset);

	mb();
	ev7csr->csr = q;
	mb();
}