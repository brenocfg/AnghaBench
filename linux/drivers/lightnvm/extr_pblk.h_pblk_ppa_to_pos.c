#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int lun; int ch; } ;
struct ppa_addr {TYPE_1__ a; } ;
struct nvm_geo {int num_ch; } ;

/* Variables and functions */

__attribute__((used)) static inline int pblk_ppa_to_pos(struct nvm_geo *geo, struct ppa_addr p)
{
	return p.a.lun * geo->num_ch + p.a.ch;
}