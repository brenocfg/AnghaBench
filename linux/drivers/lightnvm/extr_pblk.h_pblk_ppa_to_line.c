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
struct ppa_addr {int dummy; } ;
struct pblk_line {int dummy; } ;
struct pblk {struct pblk_line* lines; } ;

/* Variables and functions */
 size_t pblk_ppa_to_line_id (struct ppa_addr) ; 

__attribute__((used)) static inline struct pblk_line *pblk_ppa_to_line(struct pblk *pblk,
						 struct ppa_addr p)
{
	return &pblk->lines[pblk_ppa_to_line_id(p)];
}