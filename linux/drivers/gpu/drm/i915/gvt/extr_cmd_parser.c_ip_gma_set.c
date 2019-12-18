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
struct parser_exec_state {unsigned long ip_gma; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  update_ip_va (struct parser_exec_state*) ; 

__attribute__((used)) static inline int ip_gma_set(struct parser_exec_state *s,
		unsigned long ip_gma)
{
	WARN_ON(!IS_ALIGNED(ip_gma, 4));

	s->ip_gma = ip_gma;
	update_ip_va(s);
	return 0;
}