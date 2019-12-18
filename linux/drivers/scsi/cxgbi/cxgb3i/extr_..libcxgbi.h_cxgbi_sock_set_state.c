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
struct cxgbi_sock {int state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void cxgbi_sock_set_state(struct cxgbi_sock *csk, int state)
{
	log_debug(1 << CXGBI_DBG_SOCK,
		"csk 0x%p,%u,0x%lx, state -> %u.\n",
		csk, csk->state, csk->flags, state);
	csk->state = state;
}