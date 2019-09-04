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
struct execlist_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  port_request (struct execlist_port const*) ; 
 int rq_prio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int port_prio(const struct execlist_port *port)
{
	return rq_prio(port_request(port));
}