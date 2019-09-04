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
struct spu_state {struct spu_lscsa* lscsa; } ;
struct spu_lscsa {unsigned char* ls; } ;

/* Variables and functions */
 int ENOMEM ; 
 int LS_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageReserved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc_to_page (unsigned char*) ; 
 struct spu_lscsa* vzalloc (int) ; 

int spu_alloc_lscsa(struct spu_state *csa)
{
	struct spu_lscsa *lscsa;
	unsigned char *p;

	lscsa = vzalloc(sizeof(*lscsa));
	if (!lscsa)
		return -ENOMEM;
	csa->lscsa = lscsa;

	/* Set LS pages reserved to allow for user-space mapping. */
	for (p = lscsa->ls; p < lscsa->ls + LS_SIZE; p += PAGE_SIZE)
		SetPageReserved(vmalloc_to_page(p));

	return 0;
}