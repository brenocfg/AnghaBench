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

__attribute__((used)) static inline bool pblk_ppa_comp(struct ppa_addr lppa, struct ppa_addr rppa)
{
	return (lppa.ppa == rppa.ppa);
}