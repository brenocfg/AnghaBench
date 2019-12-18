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
struct ppa_addr {scalar_t__ ppa; } ;

/* Variables and functions */
 scalar_t__ ADDR_EMPTY ; 

__attribute__((used)) static inline int pblk_ppa_empty(struct ppa_addr ppa_addr)
{
	return (ppa_addr.ppa == ADDR_EMPTY);
}