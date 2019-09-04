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
struct lineop {int val; scalar_t__ inverted; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int port_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int line_get(const struct lineop *op)
{
	u8 oldval = port_read(op->port);

	return ((op->inverted && (oldval & op->val) != op->val)
	    || (!op->inverted && (oldval & op->val) == op->val));
}