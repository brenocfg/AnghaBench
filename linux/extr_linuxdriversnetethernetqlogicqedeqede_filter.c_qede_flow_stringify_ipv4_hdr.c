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
struct qede_arfs_tuple {scalar_t__ ip_proto; int src_port; int dst_port; int /*<<< orphan*/  dst_ipv4; int /*<<< orphan*/  src_ipv4; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  QEDE_FILTER_PRINT_MAX_LEN ; 
 int /*<<< orphan*/  snprintf (void*,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void qede_flow_stringify_ipv4_hdr(struct qede_arfs_tuple *t,
					 void *buffer)
{
	const char *prefix = t->ip_proto == IPPROTO_TCP ? "TCP" : "UDP";

	snprintf(buffer, QEDE_FILTER_PRINT_MAX_LEN,
		 "%s %pI4 (%04x) -> %pI4 (%04x)",
		 prefix, &t->src_ipv4, t->src_port,
		 &t->dst_ipv4, t->dst_port);
}