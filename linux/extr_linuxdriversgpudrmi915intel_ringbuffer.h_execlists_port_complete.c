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
struct intel_engine_execlists {unsigned int port_mask; } ;
struct execlist_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXECLISTS_ACTIVE_USER ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  execlists_is_active (struct intel_engine_execlists* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct execlist_port* const,struct execlist_port* const,unsigned int const) ; 
 int /*<<< orphan*/  memset (struct execlist_port* const,int /*<<< orphan*/ ,int) ; 
 scalar_t__ port_index (struct execlist_port* const,struct intel_engine_execlists* const) ; 

__attribute__((used)) static inline struct execlist_port *
execlists_port_complete(struct intel_engine_execlists * const execlists,
			struct execlist_port * const port)
{
	const unsigned int m = execlists->port_mask;

	GEM_BUG_ON(port_index(port, execlists) != 0);
	GEM_BUG_ON(!execlists_is_active(execlists, EXECLISTS_ACTIVE_USER));

	memmove(port, port + 1, m * sizeof(struct execlist_port));
	memset(port + m, 0, sizeof(struct execlist_port));

	return port;
}