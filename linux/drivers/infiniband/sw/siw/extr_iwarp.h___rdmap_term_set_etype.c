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
typedef  int u8 ;
struct iwarp_terminate {int etype; } ;

/* Variables and functions */

__attribute__((used)) static inline void __rdmap_term_set_etype(struct iwarp_terminate *term,
					  u8 etype)
{
	term->etype = etype & 0xf;
}