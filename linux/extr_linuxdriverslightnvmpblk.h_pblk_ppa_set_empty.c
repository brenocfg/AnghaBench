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
struct ppa_addr {int /*<<< orphan*/  ppa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EMPTY ; 

__attribute__((used)) static inline void pblk_ppa_set_empty(struct ppa_addr *ppa_addr)
{
	ppa_addr->ppa = ADDR_EMPTY;
}